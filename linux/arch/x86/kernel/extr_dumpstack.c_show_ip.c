#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pt_regs {scalar_t__ ip; scalar_t__ cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,char const*,int,...) ; 
 int /*<<< orphan*/  show_opcodes (struct pt_regs*,char const*) ; 

void show_ip(struct pt_regs *regs, const char *loglvl)
{
#ifdef CONFIG_X86_32
	printk("%sEIP: %pS\n", loglvl, (void *)regs->ip);
#else
	printk("%sRIP: %04x:%pS\n", loglvl, (int)regs->cs, (void *)regs->ip);
#endif
	show_opcodes(regs, loglvl);
}