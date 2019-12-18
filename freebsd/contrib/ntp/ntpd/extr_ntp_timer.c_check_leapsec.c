#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32 ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  lsdata ;
struct TYPE_7__ {int Q_s; } ;
struct TYPE_8__ {double tai_diff; double warped; scalar_t__ tai_offs; scalar_t__ proximity; scalar_t__ dynamic; TYPE_1__ ttime; int /*<<< orphan*/  ddist; } ;
typedef  TYPE_2__ leap_result_t ;
struct TYPE_9__ {int enabled; int in_progress; double doffset; int interval; int intv_end; int intv_start; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  DTOLFP (double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVNT_ARMED ; 
 int /*<<< orphan*/  EVNT_DISARMED ; 
 int /*<<< orphan*/  EVNT_LEAP ; 
 int FALSE ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ LSPROX_ALERT ; 
 scalar_t__ LSPROX_NOWARN ; 
 scalar_t__ LSPROX_SCHEDULE ; 
 double M_PI ; 
 int /*<<< orphan*/  PEVNT_ARMED ; 
 int TRUE ; 
 int /*<<< orphan*/  check_leap_sec_in_progress (TYPE_2__*) ; 
 double clock_max_back ; 
 double clock_max_fwd ; 
 double cos (double) ; 
 int /*<<< orphan*/  crypto_update_taichange () ; 
 scalar_t__ kern_enable ; 
 TYPE_5__ leap_smear ; 
 scalar_t__ leap_smear_intv ; 
 double leapdif ; 
 scalar_t__ leapsec ; 
 int /*<<< orphan*/  leapsec_electric (int) ; 
 int leapsec_query (TYPE_2__*,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  leapsec_reset_frame () ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pll_control ; 
 int /*<<< orphan*/  report_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  step_systime (double) ; 
 int /*<<< orphan*/ * sys_peer ; 
 scalar_t__ sys_tai ; 

__attribute__((used)) static void
check_leapsec(
	u_int32        now  ,
	const time_t * tpiv ,
        int/*BOOL*/    reset)
{
	static const char leapmsg_p_step[] =
	    "Positive leap second, stepped backward.";
	static const char leapmsg_p_slew[] =
	    "Positive leap second, no step correction. "
	    "System clock will be inaccurate for a long time.";

	static const char leapmsg_n_step[] =
	    "Negative leap second, stepped forward.";
	static const char leapmsg_n_slew[] =
	    "Negative leap second, no step correction. "
	    "System clock will be inaccurate for a long time.";

	leap_result_t lsdata;
	u_int32       lsprox;
#ifdef AUTOKEY
	int/*BOOL*/   update_autokey = FALSE;
#endif

#ifndef SYS_WINNT  /* WinNT port has its own leap second handling */
# ifdef KERNEL_PLL
	leapsec_electric(pll_control && kern_enable);
# else
	leapsec_electric(0);
# endif
#endif
#ifdef LEAP_SMEAR
	leap_smear.enabled = leap_smear_intv != 0;
#endif
	if (reset) {
		lsprox = LSPROX_NOWARN;
		leapsec_reset_frame();
		memset(&lsdata, 0, sizeof(lsdata));
	} else {
	  int fired;

	  fired = leapsec_query(&lsdata, now, tpiv);

	  DPRINTF(3, ("*** leapsec_query: fired %i, now %u (0x%08X), tai_diff %i, ddist %u\n",
		  fired, now, now, lsdata.tai_diff, lsdata.ddist));

#ifdef LEAP_SMEAR
	  leap_smear.in_progress = 0;
	  leap_smear.doffset = 0.0;

	  if (leap_smear.enabled) {
		if (lsdata.tai_diff) {
			if (leap_smear.interval == 0) {
				leap_smear.interval = leap_smear_intv;
				leap_smear.intv_end = lsdata.ttime.Q_s;
				leap_smear.intv_start = leap_smear.intv_end - leap_smear.interval;
				DPRINTF(1, ("*** leapsec_query: setting leap_smear interval %li, begin %.0f, end %.0f\n",
					leap_smear.interval, leap_smear.intv_start, leap_smear.intv_end));
			}
		} else {
			if (leap_smear.interval)
				DPRINTF(1, ("*** leapsec_query: clearing leap_smear interval\n"));
			leap_smear.interval = 0;
		}

		if (leap_smear.interval) {
			double dtemp = now;
			if (dtemp >= leap_smear.intv_start && dtemp <= leap_smear.intv_end) {
				double leap_smear_time = dtemp - leap_smear.intv_start;
				/*
				 * For now we just do a linear interpolation over the smear interval
				 */
#if 0
				// linear interpolation
				leap_smear.doffset = -(leap_smear_time * lsdata.tai_diff / leap_smear.interval);
#else
				// Google approach: lie(t) = (1.0 - cos(pi * t / w)) / 2.0
				leap_smear.doffset = -((double) lsdata.tai_diff - cos( M_PI * leap_smear_time / leap_smear.interval)) / 2.0;
#endif
				/*
				 * TODO see if we're inside an inserted leap second, so we need to compute
				 * leap_smear.doffset = 1.0 - leap_smear.doffset
				 */
				leap_smear.in_progress = 1;
#if 0 && defined( DEBUG )
				msyslog(LOG_NOTICE, "*** leapsec_query: [%.0f:%.0f] (%li), now %u (%.0f), smear offset %.6f ms\n",
					leap_smear.intv_start, leap_smear.intv_end, leap_smear.interval,
					now, leap_smear_time, leap_smear.doffset);
#else
				DPRINTF(1, ("*** leapsec_query: [%.0f:%.0f] (%li), now %u (%.0f), smear offset %.6f ms\n",
					leap_smear.intv_start, leap_smear.intv_end, leap_smear.interval,
					now, leap_smear_time, leap_smear.doffset));
#endif

			}
		}
	  }
	  else
		leap_smear.interval = 0;

	  /*
	   * Update the current leap smear offset, eventually 0.0 if outside smear interval.
	   */
	  DTOLFP(leap_smear.doffset, &leap_smear.offset);

#endif	/* LEAP_SMEAR */

	  if (fired) {
		/* Full hit. Eventually step the clock, but always
		 * announce the leap event has happened.
		 */
		const char *leapmsg = NULL;
		double      lswarp  = lsdata.warped;
		if (lswarp < 0.0) {
			if (clock_max_back > 0.0 &&
			    clock_max_back < -lswarp) {
				step_systime(lswarp);
				leapmsg = leapmsg_p_step;
			} else {
				leapmsg = leapmsg_p_slew;
			}
		} else 	if (lswarp > 0.0) {
			if (clock_max_fwd > 0.0 &&
			    clock_max_fwd < lswarp) {
				step_systime(lswarp);
				leapmsg = leapmsg_n_step;
			} else {
				leapmsg = leapmsg_n_slew;
			}
		}
		if (leapmsg)
			msyslog(LOG_NOTICE, "%s", leapmsg);
		report_event(EVNT_LEAP, NULL, NULL);
#ifdef AUTOKEY
		update_autokey = TRUE;
#endif
		lsprox  = LSPROX_NOWARN;
		leapsec = LSPROX_NOWARN;
		sys_tai = lsdata.tai_offs;
	  } else {
#ifdef AUTOKEY
		  update_autokey = (sys_tai != (u_int)lsdata.tai_offs);
#endif
		  lsprox  = lsdata.proximity;
		  sys_tai = lsdata.tai_offs;
	  }
	}

	/* We guard against panic alarming during the red alert phase.
	 * Strange and evil things might happen if we go from stone cold
	 * to piping hot in one step. If things are already that wobbly,
	 * we let the normal clock correction take over, even if a jump
	 * is involved.
         * Also make sure the alarming events are edge-triggered, that is,
         * ceated only when the threshold is crossed.
         */
	if (  (leapsec > 0 || lsprox < LSPROX_ALERT)
	    && leapsec < lsprox                     ) {
		if (  leapsec < LSPROX_SCHEDULE
                   && lsprox >= LSPROX_SCHEDULE) {
			if (lsdata.dynamic)
				report_event(PEVNT_ARMED, sys_peer, NULL);
			else
				report_event(EVNT_ARMED, NULL, NULL);
		}
		leapsec = lsprox;
	}
	if (leapsec > lsprox) {
		if (  leapsec >= LSPROX_SCHEDULE
                   && lsprox   < LSPROX_SCHEDULE) {
			report_event(EVNT_DISARMED, NULL, NULL);
		}
		leapsec = lsprox;
	}

	if (leapsec >= LSPROX_SCHEDULE)
		leapdif = lsdata.tai_diff;
	else
		leapdif = 0;

	check_leap_sec_in_progress(&lsdata);

#ifdef AUTOKEY
	if (update_autokey)
		crypto_update_taichange();
#endif
}