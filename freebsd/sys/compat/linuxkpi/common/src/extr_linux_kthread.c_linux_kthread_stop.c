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
struct task_struct {int task_ret; int /*<<< orphan*/  exited; int /*<<< orphan*/  kthread_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTHREAD_SHOULD_STOP_MASK ; 
 int /*<<< orphan*/  atomic_or (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_unpark (struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int
linux_kthread_stop(struct task_struct *task)
{
	int retval;

	/*
	 * Assume task is still alive else caller should not call
	 * kthread_stop():
	 */
	atomic_or(KTHREAD_SHOULD_STOP_MASK, &task->kthread_flags);
	kthread_unpark(task);
	wake_up_process(task);
	wait_for_completion(&task->exited);

	/*
	 * Get return code and free task structure:
	 */
	retval = task->task_ret;
	put_task_struct(task);

	return (retval);
}