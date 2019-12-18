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
struct user_pt_regs {int /*<<< orphan*/  pstate; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SPSR_SS ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 scalar_t__ is_compat_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int valid_compat_regs (struct user_pt_regs*) ; 
 int valid_native_regs (struct user_pt_regs*) ; 

int valid_user_regs(struct user_pt_regs *regs, struct task_struct *task)
{
	if (!test_tsk_thread_flag(task, TIF_SINGLESTEP))
		regs->pstate &= ~DBG_SPSR_SS;

	if (is_compat_thread(task_thread_info(task)))
		return valid_compat_regs(regs);
	else
		return valid_native_regs(regs);
}