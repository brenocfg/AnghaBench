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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  resettodr () ; 
 scalar_t__ securelevel_gt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tc_setclock (struct timespec*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,struct timeval*) ; 

__attribute__((used)) static int
settime(struct thread *td, struct timeval *tv)
{
	struct timeval delta, tv1, tv2;
	static struct timeval maxtime, laststep;
	struct timespec ts;

	microtime(&tv1);
	delta = *tv;
	timevalsub(&delta, &tv1);

	/*
	 * If the system is secure, we do not allow the time to be 
	 * set to a value earlier than 1 second less than the highest
	 * time we have yet seen. The worst a miscreant can do in
	 * this circumstance is "freeze" time. He couldn't go
	 * back to the past.
	 *
	 * We similarly do not allow the clock to be stepped more
	 * than one second, nor more than once per second. This allows
	 * a miscreant to make the clock march double-time, but no worse.
	 */
	if (securelevel_gt(td->td_ucred, 1) != 0) {
		if (delta.tv_sec < 0 || delta.tv_usec < 0) {
			/*
			 * Update maxtime to latest time we've seen.
			 */
			if (tv1.tv_sec > maxtime.tv_sec)
				maxtime = tv1;
			tv2 = *tv;
			timevalsub(&tv2, &maxtime);
			if (tv2.tv_sec < -1) {
				tv->tv_sec = maxtime.tv_sec - 1;
				printf("Time adjustment clamped to -1 second\n");
			}
		} else {
			if (tv1.tv_sec == laststep.tv_sec)
				return (EPERM);
			if (delta.tv_sec > 1) {
				tv->tv_sec = tv1.tv_sec + 1;
				printf("Time adjustment clamped to +1 second\n");
			}
			laststep = *tv;
		}
	}

	ts.tv_sec = tv->tv_sec;
	ts.tv_nsec = tv->tv_usec * 1000;
	tc_setclock(&ts);
	resettodr();
	return (0);
}