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
struct task_struct {int dummy; } ;
struct pt_regs {unsigned long flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_FORCED_TF ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 unsigned long X86_EFLAGS_TF ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_setting_trap_flag (struct task_struct*,struct pt_regs*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 int test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int enable_single_step(struct task_struct *child)
{
	struct pt_regs *regs = task_pt_regs(child);
	unsigned long oflags;

	/*
	 * If we stepped into a sysenter/syscall insn, it trapped in
	 * kernel mode; do_debug() cleared TF and set TIF_SINGLESTEP.
	 * If user-mode had set TF itself, then it's still clear from
	 * do_debug() and we need to set it again to restore the user
	 * state so we don't wrongly set TIF_FORCED_TF below.
	 * If enable_single_step() was used last and that is what
	 * set TIF_SINGLESTEP, then both TF and TIF_FORCED_TF are
	 * already set and our bookkeeping is fine.
	 */
	if (unlikely(test_tsk_thread_flag(child, TIF_SINGLESTEP)))
		regs->flags |= X86_EFLAGS_TF;

	/*
	 * Always set TIF_SINGLESTEP - this guarantees that
	 * we single-step system calls etc..  This will also
	 * cause us to set TF when returning to user mode.
	 */
	set_tsk_thread_flag(child, TIF_SINGLESTEP);

	oflags = regs->flags;

	/* Set TF on the kernel stack.. */
	regs->flags |= X86_EFLAGS_TF;

	/*
	 * ..but if TF is changed by the instruction we will trace,
	 * don't mark it as being "us" that set it, so that we
	 * won't clear it by hand later.
	 *
	 * Note that if we don't actually execute the popf because
	 * of a signal arriving right now or suchlike, we will lose
	 * track of the fact that it really was "us" that set it.
	 */
	if (is_setting_trap_flag(child, regs)) {
		clear_tsk_thread_flag(child, TIF_FORCED_TF);
		return 0;
	}

	/*
	 * If TF was already set, check whether it was us who set it.
	 * If not, we should never attempt a block step.
	 */
	if (oflags & X86_EFLAGS_TF)
		return test_tsk_thread_flag(child, TIF_FORCED_TF);

	set_tsk_thread_flag(child, TIF_FORCED_TF);

	return 1;
}