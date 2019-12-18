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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 unsigned int TASK_RUNNING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int linux_add_to_sleepqueue (void*,struct task_struct*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_task_state (struct task_struct*,unsigned int) ; 
 int /*<<< orphan*/  sleepq_lock (void*) ; 
 int /*<<< orphan*/  sleepq_release (void*) ; 

int
linux_wait_on_atomic_t(atomic_t *a, unsigned int state)
{
	struct task_struct *task;
	void *wchan;
	int ret;

	task = current;
	wchan = a;
	for (;;) {
		sleepq_lock(wchan);
		if (atomic_read(a) == 0) {
			sleepq_release(wchan);
			ret = 0;
			break;
		}
		set_task_state(task, state);
		ret = linux_add_to_sleepqueue(wchan, task, "watomic", 0, state);
		if (ret != 0)
			break;
	}
	set_task_state(task, TASK_RUNNING);

	return (ret);
}