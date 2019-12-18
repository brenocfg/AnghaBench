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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_BLOCKSTEP ; 
 int /*<<< orphan*/  TIF_FORCED_TF ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  X86_EFLAGS_TF ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_task_blockstep (struct task_struct*,int) ; 
 TYPE_1__* task_pt_regs (struct task_struct*) ; 
 scalar_t__ test_and_clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void user_disable_single_step(struct task_struct *child)
{
	/*
	 * Make sure block stepping (BTF) is disabled.
	 */
	if (test_tsk_thread_flag(child, TIF_BLOCKSTEP))
		set_task_blockstep(child, false);

	/* Always clear TIF_SINGLESTEP... */
	clear_tsk_thread_flag(child, TIF_SINGLESTEP);

	/* But touch TF only if it was set by us.. */
	if (test_and_clear_tsk_thread_flag(child, TIF_FORCED_TF))
		task_pt_regs(child)->flags &= ~X86_EFLAGS_TF;
}