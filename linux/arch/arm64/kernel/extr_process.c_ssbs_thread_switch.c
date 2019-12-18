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
struct task_struct {int flags; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARM64_SSBD_FORCE_ENABLE ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  TIF_SSBD ; 
 scalar_t__ arm64_get_ssbd_state () ; 
 scalar_t__ compat_user_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  set_compat_ssbs_bit (struct pt_regs*) ; 
 int /*<<< orphan*/  set_ssbs_bit (struct pt_regs*) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static void ssbs_thread_switch(struct task_struct *next)
{
	struct pt_regs *regs = task_pt_regs(next);

	/*
	 * Nothing to do for kernel threads, but 'regs' may be junk
	 * (e.g. idle task) so check the flags and bail early.
	 */
	if (unlikely(next->flags & PF_KTHREAD))
		return;

	/* If the mitigation is enabled, then we leave SSBS clear. */
	if ((arm64_get_ssbd_state() == ARM64_SSBD_FORCE_ENABLE) ||
	    test_tsk_thread_flag(next, TIF_SSBD))
		return;

	if (compat_user_mode(regs))
		set_compat_ssbs_bit(regs);
	else if (user_mode(regs))
		set_ssbs_bit(regs);
}