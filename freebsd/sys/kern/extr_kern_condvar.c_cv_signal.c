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
struct cv {scalar_t__ cv_waiters; } ;

/* Variables and functions */
 scalar_t__ CV_WAITERS_BOUND ; 
 int /*<<< orphan*/  SLEEPQ_CONDVAR ; 
 int /*<<< orphan*/  kick_proc0 () ; 
 int /*<<< orphan*/  sleepq_lock (struct cv*) ; 
 int /*<<< orphan*/ * sleepq_lookup (struct cv*) ; 
 int /*<<< orphan*/  sleepq_release (struct cv*) ; 
 int sleepq_signal (struct cv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cv_signal(struct cv *cvp)
{
	int wakeup_swapper;

	if (cvp->cv_waiters == 0)
		return;
	wakeup_swapper = 0;
	sleepq_lock(cvp);
	if (cvp->cv_waiters > 0) {
		if (cvp->cv_waiters == CV_WAITERS_BOUND &&
		    sleepq_lookup(cvp) == NULL) {
			cvp->cv_waiters = 0;
		} else {
			if (cvp->cv_waiters < CV_WAITERS_BOUND)
				cvp->cv_waiters--;
			wakeup_swapper = sleepq_signal(cvp, SLEEPQ_CONDVAR, 0,
			    0);
		}
	}
	sleepq_release(cvp);
	if (wakeup_swapper)
		kick_proc0();
}