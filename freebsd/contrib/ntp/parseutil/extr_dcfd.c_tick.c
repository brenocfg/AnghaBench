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
 int ADJINTERVAL ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ MAX_UNSYNC ; 
 int NOTICE_INTERVAL ; 
 scalar_t__ NO_SYNC ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ SYNC ; 
 int /*<<< orphan*/  alarm (int) ; 
 scalar_t__ last_sync ; 
 int /*<<< orphan*/  periodic_adjust () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 scalar_t__ sync_state ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int ticks ; 

__attribute__((used)) static void
tick(
     int signum
     )
{
	static unsigned long last_notice = 0;

#if !defined(HAVE_SIGACTION) && !defined(HAVE_SIGVEC)
	(void)signal(SIGALRM, tick);
#endif

	periodic_adjust();

	ticks += 1<<ADJINTERVAL;

	if ((ticks - last_sync) > MAX_UNSYNC)
	{
		/*
		 * not getting time for a while
		 */
		if (sync_state == SYNC)
		{
			/*
			 * completely lost information
			 */
			sync_state = NO_SYNC;
			syslog(LOG_INFO, "DCF77 reception lost (timeout)");
			last_notice = ticks;
		}
		else
		    /*
		     * in NO_SYNC state - look whether its time to speak up again
		     */
		    if ((ticks - last_notice) > NOTICE_INTERVAL)
		    {
			    syslog(LOG_NOTICE, "still not synchronized to DCF77 - check receiver/signal");
			    last_notice = ticks;
		    }
	}

#ifndef ITIMER_REAL
	(void) alarm(1<<ADJINTERVAL);
#endif
}