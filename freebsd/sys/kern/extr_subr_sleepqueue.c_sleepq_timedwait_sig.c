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

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int sleepq_catch_signals (void*,int) ; 
 int sleepq_check_signals () ; 
 int sleepq_check_timeout () ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

int
sleepq_timedwait_sig(void *wchan, int pri)
{
	int rcatch, rvalt, rvals;

	rcatch = sleepq_catch_signals(wchan, pri);
	rvalt = sleepq_check_timeout();
	rvals = sleepq_check_signals();
	thread_unlock(curthread);
	if (rcatch)
		return (rcatch);
	if (rvals)
		return (rvals);
	return (rvalt);
}