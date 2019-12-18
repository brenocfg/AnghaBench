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
struct timeval {int dummy; } ;
struct timespec {int dummy; } ;
struct itimerspec {struct timespec it_value; struct timespec it_interval; } ;
struct itimer {int /*<<< orphan*/  it_callout; struct itimerspec it_time; int /*<<< orphan*/  it_clockid; int /*<<< orphan*/  it_mtx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int TIMER_ABSTIME ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimer*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ itimespecfix (struct timespec*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realtimer_clocktime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  realtimer_expire ; 
 int /*<<< orphan*/  realtimer_gettime (struct itimer*,struct itimerspec*) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  timespecclear (struct timespec*) ; 
 scalar_t__ timespecisset (struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

__attribute__((used)) static int
realtimer_settime(struct itimer *it, int flags,
	struct itimerspec *value, struct itimerspec *ovalue)
{
	struct timespec cts, ts;
	struct timeval tv;
	struct itimerspec val;

	mtx_assert(&it->it_mtx, MA_OWNED);

	val = *value;
	if (itimespecfix(&val.it_value))
		return (EINVAL);

	if (timespecisset(&val.it_value)) {
		if (itimespecfix(&val.it_interval))
			return (EINVAL);
	} else {
		timespecclear(&val.it_interval);
	}
	
	if (ovalue != NULL)
		realtimer_gettime(it, ovalue);

	it->it_time = val;
	if (timespecisset(&val.it_value)) {
		realtimer_clocktime(it->it_clockid, &cts);
		ts = val.it_value;
		if ((flags & TIMER_ABSTIME) == 0) {
			/* Convert to absolute time. */
			timespecadd(&it->it_time.it_value, &cts,
				&it->it_time.it_value);
		} else {
			timespecsub(&ts, &cts, &ts);
			/*
			 * We don't care if ts is negative, tztohz will
			 * fix it.
			 */
		}
		TIMESPEC_TO_TIMEVAL(&tv, &ts);
		callout_reset(&it->it_callout, tvtohz(&tv),
			realtimer_expire, it);
	} else {
		callout_stop(&it->it_callout);
	}

	return (0);
}