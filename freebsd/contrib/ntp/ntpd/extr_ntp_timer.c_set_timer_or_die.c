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
typedef  int /*<<< orphan*/  intervaltimer ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  itimer ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const*) ; 
 int setitimer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_id ; 
 int timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
set_timer_or_die(
	const intervaltimer *	ptimer
	)
{
	const char *	setfunc;
	int		rc;

# ifdef HAVE_TIMER_CREATE
	setfunc = "timer_settime";
	rc = timer_settime(timer_id, 0, &itimer, NULL);
# else
	setfunc = "setitimer";
	rc = setitimer(ITIMER_REAL, &itimer, NULL);
# endif
	if (-1 == rc) {
		msyslog(LOG_ERR, "interval timer %s failed, %m",
			setfunc);
		exit(1);
	}
}