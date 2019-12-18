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
typedef  int time_t ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  DTOLFP (double,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  L_ADD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  _clear_adjtime () ; 
 scalar_t__ allow_panic ; 
 int basedate_get_eracenter () ; 
 scalar_t__ enable_panic_check ; 
 int /*<<< orphan*/  get_ostime (struct timespec*) ; 
 int lamport_violated ; 
 struct timeval lfp_stamp_to_tval (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ntp_set_tod (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  step_callback () ; 
 int /*<<< orphan*/  stub1 () ; 
 double sys_residual ; 
 int /*<<< orphan*/  tspec_stamp_to_lfp (struct timespec) ; 
 int /*<<< orphan*/  update_uwtmp (struct timeval,struct timeval) ; 

int
step_systime(
	double step
	)
{
	time_t pivot; /* for ntp era unfolding */
	struct timeval timetv, tvlast;
	struct timespec timets;
	l_fp fp_ofs, fp_sys; /* offset and target system time in FP */

	/*
	 * Get pivot time for NTP era unfolding. Since we don't step
	 * very often, we can afford to do the whole calculation from
	 * scratch. And we're not in the time-critical path yet.
	 */
#if SIZEOF_TIME_T > 4
	pivot = basedate_get_eracenter();
#else
	/* This makes sure the resulting time stamp is on or after
	 * 1969-12-31/23:59:59 UTC and gives us additional two years,
	 * from the change of NTP era in 2036 to the UNIX rollover in
	 * 2038. (Minus one second, but that won't hurt.) We *really*
	 * need a longer 'time_t' after that!  Or a different baseline,
	 * but that would cause other serious trouble, too.
	 */
	pivot = 0x7FFFFFFF;
#endif

	/* get the complete jump distance as l_fp */
	DTOLFP(sys_residual, &fp_sys);
	DTOLFP(step,         &fp_ofs);
	L_ADD(&fp_ofs, &fp_sys);

	/* ---> time-critical path starts ---> */

	/* get the current time as l_fp (without fuzz) and as struct timeval */
	get_ostime(&timets);
	fp_sys = tspec_stamp_to_lfp(timets);
	tvlast.tv_sec = timets.tv_sec;
	tvlast.tv_usec = (timets.tv_nsec + 500) / 1000;

	/* get the target time as l_fp */
	L_ADD(&fp_sys, &fp_ofs);

	/* unfold the new system time */
	timetv = lfp_stamp_to_tval(fp_sys, &pivot);

	/* now set new system time */
	if (ntp_set_tod(&timetv, NULL) != 0) {
		msyslog(LOG_ERR, "step-systime: %m");
		if (enable_panic_check && allow_panic) {
			msyslog(LOG_ERR, "step_systime: allow_panic is TRUE!");
		}
		return FALSE;
	}

	/* <--- time-critical path ended with 'ntp_set_tod()' <--- */

	sys_residual = 0;
	lamport_violated = (step < 0);
	if (step_callback)
		(*step_callback)();

#ifdef NEED_HPUX_ADJTIME
	/*
	 * CHECKME: is this correct when called by ntpdate?????
	 */
	_clear_adjtime();
#endif

	update_uwtmp(timetv, tvlast);
	if (enable_panic_check && allow_panic) {
		msyslog(LOG_ERR, "step_systime: allow_panic is TRUE!");
		INSIST(!allow_panic);
	}
	return TRUE;
}