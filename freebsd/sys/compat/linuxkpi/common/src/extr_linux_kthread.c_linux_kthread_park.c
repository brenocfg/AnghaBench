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
struct task_struct {int /*<<< orphan*/  parked; int /*<<< orphan*/  kthread_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTHREAD_SHOULD_PARK_MASK ; 
 int /*<<< orphan*/  atomic_or (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int
linux_kthread_park(struct task_struct *task)
{

	atomic_or(KTHREAD_SHOULD_PARK_MASK, &task->kthread_flags);
	wake_up_process(task);
	wait_for_completion(&task->parked);
	return (0);
}