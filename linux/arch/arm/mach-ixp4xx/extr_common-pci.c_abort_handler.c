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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int ARM_pc; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PCI_ISR ; 
 int /*<<< orphan*/  PCI_ISR_PFE ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int /*<<< orphan*/  PCI_STATUS_REC_MASTER_ABORT ; 
 int /*<<< orphan*/  local_read_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_write_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abort_handler(unsigned long addr, unsigned int fsr, struct pt_regs *regs)
{
	u32 isr, status;

	isr = *PCI_ISR;
	local_read_config(PCI_STATUS, 2, &status);
	pr_debug("PCI: abort_handler addr = %#lx, isr = %#x, "
		"status = %#x\n", addr, isr, status);

	/* make sure the Master Abort bit is reset */    
	*PCI_ISR = PCI_ISR_PFE;
	status |= PCI_STATUS_REC_MASTER_ABORT;
	local_write_config(PCI_STATUS, 2, status);

	/*
	 * If it was an imprecise abort, then we need to correct the
	 * return address to be _after_ the instruction.
	 */
	if (fsr & (1 << 10))
		regs->ARM_pc += 4;

	return 0;
}