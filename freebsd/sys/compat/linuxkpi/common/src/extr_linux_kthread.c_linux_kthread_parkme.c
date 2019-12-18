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
struct task_struct {int /*<<< orphan*/  kthread_flags; int /*<<< orphan*/  parked; } ;

/* Variables and functions */
 int KTHREAD_IS_PARKED_MASK ; 
 int TASK_PARKED ; 
 int TASK_RUNNING ; 
 int TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int atomic_fetch_or (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 scalar_t__ linux_kthread_should_park () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_task_state (struct task_struct*,int) ; 

void
linux_kthread_parkme(void)
{
	struct task_struct *task;

	task = current;
	set_task_state(task, TASK_PARKED | TASK_UNINTERRUPTIBLE);
	while (linux_kthread_should_park()) {
		while ((atomic_fetch_or(KTHREAD_IS_PARKED_MASK,
		    &task->kthread_flags) & KTHREAD_IS_PARKED_MASK) == 0)
			complete(&task->parked);
		schedule();
		set_task_state(task, TASK_PARKED | TASK_UNINTERRUPTIBLE);
	}
	atomic_andnot(KTHREAD_IS_PARKED_MASK, &task->kthread_flags);
	set_task_state(task, TASK_RUNNING);
}