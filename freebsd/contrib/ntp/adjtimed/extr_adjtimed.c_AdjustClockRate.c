#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; long tv_usec; } ;
struct TYPE_4__ {long tv_sec; long tv_usec; } ;
struct TYPE_3__ {long tv_sec; long tv_usec; } ;
struct itimerval {TYPE_2__ it_value; TYPE_1__ it_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 long MILLION ; 
 int SetClockRate (scalar_t__) ; 
 scalar_t__ default_rate ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 long oldrate ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,long,...) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 long slew_rate ; 
 int sysdebug ; 
 long tick_rate ; 
 int verbose ; 

int
AdjustClockRate(
	register struct timeval *delta,
	register struct timeval *olddelta
	)
{
	register long rate, dt, leftover;
	struct itimerval period, remains;
 
	dt = (delta->tv_sec * MILLION) + delta->tv_usec;

	if (verbose)
	    printf("adjtimed: new correction %.6fs\n", (double)dt / (double)MILLION);
	if (sysdebug)
	    msyslog(LOG_INFO, "new correction %.6fs", (double)dt / (double)MILLION);
	if (verbose > 2) printf("adjtimed: leftover %ldus\n", leftover);
	if (sysdebug > 2) msyslog(LOG_INFO, "leftover %ldus", leftover);
	rate = dt;

	/*
	 * Apply a slew rate of slew_rate over a period of dt/slew_rate seconds.
	 */
	if (dt > 0) {
		rate = slew_rate;
	} else {
		rate = -slew_rate;
		dt = -dt;
	}
	period.it_value.tv_sec = dt / slew_rate;
	period.it_value.tv_usec = (dt % slew_rate) * (MILLION / slew_rate);
	/*
	 * Note: we assume the kernel will convert the specified period into ticks
	 * using the modified clock rate rather than an assumed nominal clock rate,
	 * and therefore will generate the timer interrupt after the specified
	 * number of true seconds, not skewed seconds.
	 */

	if (verbose > 1)
	    printf("adjtimed: will be complete in %lds %ldus\n",
		   period.it_value.tv_sec, period.it_value.tv_usec);
	if (sysdebug > 1)
	    msyslog(LOG_INFO, "will be complete in %lds %ldus",
		    period.it_value.tv_sec, period.it_value.tv_usec);
	/*
	 * adjust the clock rate
	 */
	if (dt) {
		if (SetClockRate((rate / tick_rate) + default_rate) == -1) {
			msyslog(LOG_ERR, "set clock rate: %m");
			perror("adjtimed: set clock rate");
		}
	}
	/*
	 * start the timer
	 * (do this after changing the rate because the period has been rounded down)
	 */
	period.it_interval.tv_sec = period.it_interval.tv_usec = 0L;
	setitimer(ITIMER_REAL, &period, &remains);
	/*
	 * return old delta
	 */
	if (olddelta) {
		dt = ((remains.it_value.tv_sec * MILLION) + remains.it_value.tv_usec) *
			oldrate;
		olddelta->tv_sec = dt / MILLION;
		olddelta->tv_usec = dt - (olddelta->tv_sec * MILLION); 
	}

	oldrate = (double)rate / (double)MILLION;
	return(0);
}