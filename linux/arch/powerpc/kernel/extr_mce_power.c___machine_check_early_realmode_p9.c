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
struct pt_regs {int dsisr; int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 scalar_t__ SRR1_MC_LOADSTORE (int /*<<< orphan*/ ) ; 
 long mce_handle_error (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_p9_derror_table ; 
 int /*<<< orphan*/  mce_p9_ierror_table ; 

long __machine_check_early_realmode_p9(struct pt_regs *regs)
{
	/*
	 * On POWER9 DD2.1 and below, it's possible to get a machine check
	 * caused by a paste instruction where only DSISR bit 25 is set. This
	 * will result in the MCE handler seeing an unknown event and the kernel
	 * crashing. An MCE that occurs like this is spurious, so we don't need
	 * to do anything in terms of servicing it. If there is something that
	 * needs to be serviced, the CPU will raise the MCE again with the
	 * correct DSISR so that it can be serviced properly. So detect this
	 * case and mark it as handled.
	 */
	if (SRR1_MC_LOADSTORE(regs->msr) && regs->dsisr == 0x02000000)
		return 1;

	return mce_handle_error(regs, mce_p9_derror_table, mce_p9_ierror_table);
}