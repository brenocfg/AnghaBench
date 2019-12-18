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
struct pt_regs {int cp0_cause; int /*<<< orphan*/  cp0_epc; } ;

/* Variables and functions */
 int MIPS_BE_FIXUP ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  dump_tlb_all () ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 

__attribute__((used)) static int ip32_be_handler(struct pt_regs *regs, int is_fixup)
{
	int data = regs->cp0_cause & 4;

	if (is_fixup)
		return MIPS_BE_FIXUP;

	printk("Got %cbe at 0x%lx\n", data ? 'd' : 'i', regs->cp0_epc);
	show_regs(regs);
	dump_tlb_all();
	while(1);
	force_sig(SIGBUS);
}