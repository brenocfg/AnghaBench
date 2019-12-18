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
typedef  int /*<<< orphan*/  wait_queue_t ;
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct task_struct {TYPE_1__* task_thread; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  PHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRELE (int /*<<< orphan*/ ) ; 
 scalar_t__ TASK_WAKING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int linux_add_to_sleepqueue (struct task_struct*,struct task_struct*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  sleepq_lock (struct task_struct*) ; 
 int /*<<< orphan*/  sleepq_release (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
linux_wait_event_common(wait_queue_head_t *wqh, wait_queue_t *wq, int timeout,
    unsigned int state, spinlock_t *lock)
{
	struct task_struct *task;
	int ret;

	if (lock != NULL)
		spin_unlock_irq(lock);

	/* range check timeout */
	if (timeout < 1)
		timeout = 1;
	else if (timeout == MAX_SCHEDULE_TIMEOUT)
		timeout = 0;

	task = current;

	/*
	 * Our wait queue entry is on the stack - make sure it doesn't
	 * get swapped out while we sleep.
	 */
	PHOLD(task->task_thread->td_proc);
	sleepq_lock(task);
	if (atomic_read(&task->state) != TASK_WAKING) {
		ret = linux_add_to_sleepqueue(task, task, "wevent", timeout,
		    state);
	} else {
		sleepq_release(task);
		ret = 0;
	}
	PRELE(task->task_thread->td_proc);

	if (lock != NULL)
		spin_lock_irq(lock);
	return (ret);
}