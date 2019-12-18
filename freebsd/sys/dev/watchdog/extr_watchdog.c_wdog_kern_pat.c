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
typedef  int u_int ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int WD_INTERVAL ; 
 int WD_LASTVAL ; 
 int WD_TO_NEVER ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int hz ; 
 int kern_clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 
 int pow2ns_to_ticks (int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  watchdog_list ; 
 int wd_last_u ; 
 int wd_last_u_sysctl ; 
 int wd_last_u_sysctl_secs ; 
 int /*<<< orphan*/  wd_lastpat ; 
 int wd_lastpat_valid ; 
 int /*<<< orphan*/  wd_pretimeout ; 
 int /*<<< orphan*/  wd_set_pretimeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wd_softtimeo_handle ; 
 scalar_t__ wd_softtimer ; 
 int /*<<< orphan*/  wd_timeout_cb ; 
 int /*<<< orphan*/  wdog_software_attach () ; 

int
wdog_kern_pat(u_int utim)
{
	int error;
	static int first = 1;

	if ((utim & WD_LASTVAL) != 0 && (utim & WD_INTERVAL) > 0)
		return (EINVAL);

	if ((utim & WD_LASTVAL) != 0) {
		/*
		 * if WD_LASTVAL is set, fill in the bits for timeout
		 * from the saved value in wd_last_u.
		 */
		MPASS((wd_last_u & ~WD_INTERVAL) == 0);
		utim &= ~WD_LASTVAL;
		utim |= wd_last_u;
	} else {
		/*
		 * Otherwise save the new interval.
		 * This can be zero (to disable the watchdog)
		 */
		wd_last_u = (utim & WD_INTERVAL);
		wd_last_u_sysctl = wd_last_u;
		wd_last_u_sysctl_secs = pow2ns_to_ticks(wd_last_u) / hz;
	}
	if ((utim & WD_INTERVAL) == WD_TO_NEVER) {
		utim = 0;

		/* Assume all is well; watchdog signals failure. */
		error = 0;
	} else {
		/* Assume no watchdog available; watchdog flags success */
		error = EOPNOTSUPP;
	}
	if (wd_softtimer) {
		if (utim == 0) {
			callout_stop(&wd_softtimeo_handle);
		} else {
			(void) callout_reset(&wd_softtimeo_handle,
			    pow2ns_to_ticks(utim), wd_timeout_cb, "soft");
		}
		error = 0;
	} else {
		EVENTHANDLER_INVOKE(watchdog_list, utim, &error);
	}
	/*
	 * If we no hardware watchdog responded, we have not tried to
	 * attach an external software watchdog, and one is available,
	 * attach it now and retry.
	 */
	if (error == EOPNOTSUPP && first && *wdog_software_attach != NULL) {
		(*wdog_software_attach)();
		EVENTHANDLER_INVOKE(watchdog_list, utim, &error);
	}
	first = 0;

	wd_set_pretimeout(wd_pretimeout, true);
	/*
	 * If we were able to arm/strobe the watchdog, then
	 * update the last time it was strobed for WDIOC_GETTIMELEFT
	 */
	if (!error) {
		struct timespec ts;

		error = kern_clock_gettime(curthread /* XXX */,
		    CLOCK_MONOTONIC_FAST, &ts);
		if (!error) {
			wd_lastpat = ts.tv_sec;
			wd_lastpat_valid = 1;
		}
	}
	return (error);
}