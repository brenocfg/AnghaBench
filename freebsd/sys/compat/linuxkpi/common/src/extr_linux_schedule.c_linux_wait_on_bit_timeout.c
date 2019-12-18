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

/* Variables and functions */
 int MAX_SCHEDULE_TIMEOUT ; 
 unsigned int TASK_RUNNING ; 
 void* bit_to_wchan (unsigned long*,int) ; 
 struct task_struct* current ; 
 int linux_add_to_sleepqueue (void*,struct task_struct*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  set_task_state (struct task_struct*,unsigned int) ; 
 int /*<<< orphan*/  sleepq_lock (void*) ; 
 int /*<<< orphan*/  sleepq_release (void*) ; 

int
linux_wait_on_bit_timeout(unsigned long *word, int bit, unsigned int state,
    int timeout)
{
	struct task_struct *task;
	void *wchan;
	int ret;

	/* range check timeout */
	if (timeout < 1)
		timeout = 1;
	else if (timeout == MAX_SCHEDULE_TIMEOUT)
		timeout = 0;

	task = current;
	wchan = bit_to_wchan(word, bit);
	for (;;) {
		sleepq_lock(wchan);
		if ((*word & (1 << bit)) == 0) {
			sleepq_release(wchan);
			ret = 0;
			break;
		}
		set_task_state(task, state);
		ret = linux_add_to_sleepqueue(wchan, task, "wbit", timeout,
		    state);
		if (ret != 0)
			break;
	}
	set_task_state(task, TASK_RUNNING);

	return (ret);
}