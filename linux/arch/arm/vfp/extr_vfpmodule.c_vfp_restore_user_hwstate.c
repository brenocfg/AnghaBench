#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfp_hard_struct {unsigned long fpexc; int /*<<< orphan*/  fpinst2; int /*<<< orphan*/  fpinst; int /*<<< orphan*/  fpscr; int /*<<< orphan*/  fpregs; } ;
struct user_vfp_exc {unsigned long fpexc; int /*<<< orphan*/  fpinst2; int /*<<< orphan*/  fpinst; } ;
struct user_vfp {int /*<<< orphan*/  fpscr; int /*<<< orphan*/  fpregs; } ;
struct TYPE_2__ {struct vfp_hard_struct hard; } ;
struct thread_info {TYPE_1__ vfpstate; } ;

/* Variables and functions */
 unsigned long FPEXC_EN ; 
 unsigned long FPEXC_EX ; 
 unsigned long FPEXC_FP2V ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfp_flush_hwstate (struct thread_info*) ; 

int vfp_restore_user_hwstate(struct user_vfp *ufp, struct user_vfp_exc *ufp_exc)
{
	struct thread_info *thread = current_thread_info();
	struct vfp_hard_struct *hwstate = &thread->vfpstate.hard;
	unsigned long fpexc;

	/* Disable VFP to avoid corrupting the new thread state. */
	vfp_flush_hwstate(thread);

	/*
	 * Copy the floating point registers. There can be unused
	 * registers see asm/hwcap.h for details.
	 */
	memcpy(&hwstate->fpregs, &ufp->fpregs, sizeof(hwstate->fpregs));
	/*
	 * Copy the status and control register.
	 */
	hwstate->fpscr = ufp->fpscr;

	/*
	 * Sanitise and restore the exception registers.
	 */
	fpexc = ufp_exc->fpexc;

	/* Ensure the VFP is enabled. */
	fpexc |= FPEXC_EN;

	/* Ensure FPINST2 is invalid and the exception flag is cleared. */
	fpexc &= ~(FPEXC_EX | FPEXC_FP2V);
	hwstate->fpexc = fpexc;

	hwstate->fpinst = ufp_exc->fpinst;
	hwstate->fpinst2 = ufp_exc->fpinst2;

	return 0;
}