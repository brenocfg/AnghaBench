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
 int /*<<< orphan*/  DROP_GIANT () ; 
 int ERESTARTSYS ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int SLEEPQ_INTERRUPTIBLE ; 
 int SLEEPQ_SLEEP ; 
 int TASK_INTERRUPTIBLE ; 
 int TASK_NORMAL ; 
 int TASK_PARKED ; 
 int /*<<< orphan*/  linux_schedule_save_interrupt_value (struct task_struct*,int) ; 
 int /*<<< orphan*/  sleepq_add (void*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_set_timeout (void*,int) ; 
 int sleepq_timedwait (void*,int /*<<< orphan*/ ) ; 
 int sleepq_timedwait_sig (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_wait (void*,int /*<<< orphan*/ ) ; 
 int sleepq_wait_sig (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_add_to_sleepqueue(void *wchan, struct task_struct *task,
    const char *wmesg, int timeout, int state)
{
	int flags, ret;

	MPASS((state & ~(TASK_PARKED | TASK_NORMAL)) == 0);

	flags = SLEEPQ_SLEEP | ((state & TASK_INTERRUPTIBLE) != 0 ?
	    SLEEPQ_INTERRUPTIBLE : 0);

	sleepq_add(wchan, NULL, wmesg, flags, 0);
	if (timeout != 0)
		sleepq_set_timeout(wchan, timeout);

	DROP_GIANT();
	if ((state & TASK_INTERRUPTIBLE) != 0) {
		if (timeout == 0)
			ret = -sleepq_wait_sig(wchan, 0);
		else
			ret = -sleepq_timedwait_sig(wchan, 0);
	} else {
		if (timeout == 0) {
			sleepq_wait(wchan, 0);
			ret = 0;
		} else
			ret = -sleepq_timedwait(wchan, 0);
	}
	PICKUP_GIANT();

	/* filter return value */
	if (ret != 0 && ret != -EWOULDBLOCK) {
		linux_schedule_save_interrupt_value(task, ret);
		ret = -ERESTARTSYS;
	}
	return (ret);
}