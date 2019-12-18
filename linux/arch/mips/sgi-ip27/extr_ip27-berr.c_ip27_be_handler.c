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
 void* LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int MIPS_BE_FIXUP ; 
 int /*<<< orphan*/  PI_CPU_NUM ; 
 int /*<<< orphan*/  PI_ERR_INT_PEND ; 
 int /*<<< orphan*/  PI_ERR_STATUS0_A ; 
 int /*<<< orphan*/  PI_ERR_STATUS0_B ; 
 int /*<<< orphan*/  PI_ERR_STATUS1_A ; 
 int /*<<< orphan*/  PI_ERR_STATUS1_B ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  dump_hub_information (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dump_tlb_all () ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 

int ip27_be_handler(struct pt_regs *regs, int is_fixup)
{
	unsigned long errst0, errst1;
	int data = regs->cp0_cause & 4;
	int cpu = LOCAL_HUB_L(PI_CPU_NUM);

	if (is_fixup)
		return MIPS_BE_FIXUP;

	printk("Slice %c got %cbe at 0x%lx\n", 'A' + cpu, data ? 'd' : 'i',
	       regs->cp0_epc);
	printk("Hub information:\n");
	printk("ERR_INT_PEND = 0x%06llx\n", LOCAL_HUB_L(PI_ERR_INT_PEND));
	errst0 = LOCAL_HUB_L(cpu ? PI_ERR_STATUS0_B : PI_ERR_STATUS0_A);
	errst1 = LOCAL_HUB_L(cpu ? PI_ERR_STATUS1_B : PI_ERR_STATUS1_A);
	dump_hub_information(errst0, errst1);
	show_regs(regs);
	dump_tlb_all();
	while(1);
	force_sig(SIGBUS);
}