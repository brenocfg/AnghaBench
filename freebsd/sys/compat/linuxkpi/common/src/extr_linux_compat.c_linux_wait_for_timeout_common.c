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
struct completion {scalar_t__ done; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_GIANT () ; 
 int ERESTARTSYS ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int SLEEPQ_INTERRUPTIBLE ; 
 int SLEEPQ_SLEEP ; 
 scalar_t__ UINT_MAX ; 
 struct task_struct* current ; 
 int jiffies ; 
 int /*<<< orphan*/  linux_schedule_save_interrupt_value (struct task_struct*,int) ; 
 int linux_timer_jiffies_until (int) ; 
 int /*<<< orphan*/  sleepq_add (struct completion*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (struct completion*) ; 
 int /*<<< orphan*/  sleepq_release (struct completion*) ; 
 int /*<<< orphan*/  sleepq_set_timeout (struct completion*,int) ; 
 int sleepq_timedwait (struct completion*,int /*<<< orphan*/ ) ; 
 int sleepq_timedwait_sig (struct completion*,int /*<<< orphan*/ ) ; 

int
linux_wait_for_timeout_common(struct completion *c, int timeout, int flags)
{
	struct task_struct *task;
	int end = jiffies + timeout;
	int error;

	if (SCHEDULER_STOPPED())
		return (0);

	task = current;

	if (flags != 0)
		flags = SLEEPQ_INTERRUPTIBLE | SLEEPQ_SLEEP;
	else
		flags = SLEEPQ_SLEEP;

	for (;;) {
		sleepq_lock(c);
		if (c->done)
			break;
		sleepq_add(c, NULL, "completion", flags, 0);
		sleepq_set_timeout(c, linux_timer_jiffies_until(end));

		DROP_GIANT();
		if (flags & SLEEPQ_INTERRUPTIBLE)
			error = -sleepq_timedwait_sig(c, 0);
		else
			error = -sleepq_timedwait(c, 0);
		PICKUP_GIANT();

		if (error != 0) {
			/* check for timeout */
			if (error == -EWOULDBLOCK) {
				error = 0;	/* timeout */
			} else {
				/* signal happened */
				linux_schedule_save_interrupt_value(task, error);
				error = -ERESTARTSYS;
			}
			goto done;
		}
	}
	if (c->done != UINT_MAX)
		c->done--;
	sleepq_release(c);

	/* return how many jiffies are left */
	error = linux_timer_jiffies_until(end);
done:
	return (error);
}