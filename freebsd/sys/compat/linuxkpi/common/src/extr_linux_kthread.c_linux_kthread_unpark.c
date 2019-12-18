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
struct task_struct {int /*<<< orphan*/  kthread_flags; } ;

/* Variables and functions */
 int KTHREAD_IS_PARKED_MASK ; 
 int /*<<< orphan*/  KTHREAD_SHOULD_PARK_MASK ; 
 int /*<<< orphan*/  TASK_PARKED ; 
 int /*<<< orphan*/  atomic_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atomic_fetch_andnot (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 

void
linux_kthread_unpark(struct task_struct *task)
{

	atomic_andnot(KTHREAD_SHOULD_PARK_MASK, &task->kthread_flags);
	if ((atomic_fetch_andnot(KTHREAD_IS_PARKED_MASK, &task->kthread_flags) &
	    KTHREAD_IS_PARKED_MASK) != 0)
		wake_up_state(task, TASK_PARKED);
}