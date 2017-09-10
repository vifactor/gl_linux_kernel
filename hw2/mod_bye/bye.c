
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/bug.h>
#include <linux/types.h>
#include <linux/slab.h>


MODULE_AUTHOR("Viktor Kopp <vifactor@gmail.com>");
MODULE_DESCRIPTION("Goodbye in Linux Kernel Training homework.");
MODULE_LICENSE("Dual BSD/GPL");

extern void print_hello(void);

/*
 nb of times print_hello function is called.
 Special cases:
   - nb_print == 0 invoke WARN_ON(),
   - nb_print > 10 invoke BUG_ON(),
   - nb_print == 2 increment usage counter,
   - nb_print == 5 return -EINVAL.
    Default: 1
*/
static short int nb_print = 1;

module_param(nb_print, short, S_IRUGO);
MODULE_PARM_DESC(nb_print, "Nb of times print_hello is called.");

void print_goodbye(void)
{
    printk(KERN_EMERG "Goodbye!\n");
}

static int __init bye_init(void)
{
    int i = 0;	
    
    printk(KERN_EMERG "Loading module bye.\n");    

    WARN_ON(nb_print == 0);
    BUG_ON(nb_print > 10);  

    for (i = 0; i < nb_print; ++i)        
        print_hello();
    if (nb_print == 2) {
        try_module_get(THIS_MODULE);
    } else if (nb_print == 3) {
        u8* ptr = (u8*)__kmalloc;
        *ptr = 0x90;    
    } else if (nb_print == 5) {
        return -EINVAL;
    }    
	return 0;
}

static void __exit bye_exit(void)
{
	print_goodbye();
}

module_init(bye_init);
module_exit(bye_exit);
