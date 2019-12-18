#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long tv_sec; long tv_usec; } ;
struct itimerval {TYPE_1__ it_value; } ;

/* Variables and functions */
 scalar_t__ GetClockRate () ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SetClockRate (scalar_t__) ; 
 scalar_t__ default_rate ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 double oldrate ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 int sysdebug ; 
 int verbose ; 

void
ResetClockRate(void)
{
	struct itimerval it;

	it.it_value.tv_sec = it.it_value.tv_usec = 0L;
	setitimer(ITIMER_REAL, &it, (struct itimerval *)0);

	if (verbose > 2) puts("adjtimed: resetting the clock");
	if (sysdebug > 2) msyslog(LOG_INFO, "resetting the clock");

	if (GetClockRate() != default_rate) {
		if (SetClockRate(default_rate) == -1) {
			msyslog(LOG_ERR, "set clock rate: %m");
			perror("adjtimed: set clock rate");
		}
	}

	oldrate = 0.0;
}