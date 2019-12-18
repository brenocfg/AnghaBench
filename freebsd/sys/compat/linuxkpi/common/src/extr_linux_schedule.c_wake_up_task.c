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
struct task_struct {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLEEPQ_SLEEP ; 
 int /*<<< orphan*/  TASK_WAKING ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kick_proc0 () ; 
 int /*<<< orphan*/  set_task_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (struct task_struct*) ; 
 int /*<<< orphan*/  sleepq_release (struct task_struct*) ; 
 int sleepq_signal (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wake_up_task(struct task_struct *task, unsigned int state)
{
	int ret, wakeup_swapper;

	ret = wakeup_swapper = 0;
	sleepq_lock(task);
	if ((atomic_read(&task->state) & state) != 0) {
		set_task_state(task, TASK_WAKING);
		wakeup_swapper = sleepq_signal(task, SLEEPQ_SLEEP, 0, 0);
		ret = 1;
	}
	sleepq_release(task);
	if (wakeup_swapper)
		kick_proc0();
	return (ret);
}