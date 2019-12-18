#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;
struct TYPE_14__ {scalar_t__ l_i; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  DTOLFP (double,TYPE_1__*) ; 
 int /*<<< orphan*/  ENTER_GET_SYSTIME_CRITSEC () ; 
 int FALSE ; 
 int FRAC ; 
 int /*<<< orphan*/  LEAVE_GET_SYSTIME_CRITSEC () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  L_ADD (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  L_ADDUF (TYPE_1__*,int) ; 
 int /*<<< orphan*/  L_ISZERO (TYPE_1__*) ; 
 int /*<<< orphan*/  L_NEG (TYPE_1__*) ; 
 int /*<<< orphan*/  L_SUB (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  L_SUBUF (TYPE_1__*,int) ; 
 int /*<<< orphan*/  USING_SIGIO () ; 
 struct timespec add_tspec_ns (struct timespec,int) ; 
 scalar_t__ cmp_tspec (struct timespec,struct timespec) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_ostime (struct timespec*) ; 
 int lamport_violated ; 
 int /*<<< orphan*/  lfptoa (TYPE_1__*,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int ntp_random () ; 
 struct timespec sub_tspec (struct timespec,struct timespec) ; 
 int sys_fuzz ; 
 int sys_fuzz_nsec ; 
 int /*<<< orphan*/  sys_lamport ; 
 int /*<<< orphan*/  sys_tsrounding ; 
 int /*<<< orphan*/  systime_init_done ; 
 TYPE_1__ tspec_stamp_to_lfp (struct timespec) ; 

void
get_systime(
	l_fp *now		/* system time */
	)
{
        static struct timespec  ts_last;        /* last sampled os time */
	static struct timespec	ts_prev;	/* prior os time */
	static l_fp		lfp_prev;	/* prior result */
	struct timespec ts;	/* seconds and nanoseconds */
	struct timespec ts_min;	/* earliest permissible */
	struct timespec ts_lam;	/* lamport fictional increment */
	double	dfuzz;
	l_fp	result;
	l_fp	lfpfuzz;
	l_fp	lfpdelta;

	get_ostime(&ts);
	DEBUG_REQUIRE(systime_init_done);
	ENTER_GET_SYSTIME_CRITSEC();

        /* First check if here was a Lamport violation, that is, two
         * successive calls to 'get_ostime()' resulted in negative
         * time difference. Use a few milliseconds of permissible
         * tolerance -- being too sharp can hurt here. (This is intented
         * for the Win32 target, where the HPC interpolation might
         * introduce small steps backward. It should not be an issue on
         * systems where get_ostime() results in a true syscall.)
         */
        if (cmp_tspec(add_tspec_ns(ts, 50000000), ts_last) < 0) {
                lamport_violated = 1;
                sys_lamport++;
	}
        ts_last = ts;

	/*
	 * After default_get_precision() has set a nonzero sys_fuzz,
	 * ensure every reading of the OS clock advances by at least
	 * sys_fuzz over the prior reading, thereby assuring each
	 * fuzzed result is strictly later than the prior.  Limit the
	 * necessary fiction to 1 second.
	 */
	if (!USING_SIGIO()) {
		ts_min = add_tspec_ns(ts_prev, sys_fuzz_nsec);
		if (cmp_tspec(ts, ts_min) < 0) {
			ts_lam = sub_tspec(ts_min, ts);
			if (ts_lam.tv_sec > 0 && !lamport_violated) {
				msyslog(LOG_ERR,
					"get_systime Lamport advance exceeds one second (%.9f)",
					ts_lam.tv_sec +
					    1e-9 * ts_lam.tv_nsec);
				exit(1);
			}
			if (!lamport_violated)
				ts = ts_min;
		}
		ts_prev = ts;
	}

	/* convert from timespec to l_fp fixed-point */
	result = tspec_stamp_to_lfp(ts);

	/*
	 * Add in the fuzz. 'ntp_random()' returns [0..2**31-1] so we
	 * must scale up the result by 2.0 to cover the full fractional
	 * range.
	 */
	dfuzz = ntp_random() * 2. / FRAC * sys_fuzz;
	DTOLFP(dfuzz, &lfpfuzz);
	L_ADD(&result, &lfpfuzz);

	/*
	 * Ensure result is strictly greater than prior result (ignoring
	 * sys_residual's effect for now) once sys_fuzz has been
	 * determined.
	 *
	 * [Bug 3450] Rounding errors and time slew can lead to a
	 * violation of the expected postcondition. This is bound to
	 * happen from time to time (depending on state of the random
	 * generator, the current slew and the closeness of system time
	 * stamps drawn) and does not warrant a syslog entry. Instead it
	 * makes much more sense to ensure the postcondition and hop
	 * along silently.
	 */
	if (!USING_SIGIO()) {
		if (   !L_ISZERO(&lfp_prev)
		    && !lamport_violated
		    && (sys_fuzz > 0.0)
		   ) {
			lfpdelta = result;
			L_SUB(&lfpdelta, &lfp_prev);
			L_SUBUF(&lfpdelta, 1);
			if (lfpdelta.l_i < 0)
			{
				L_NEG(&lfpdelta);
				DPRINTF(1, ("get_systime: postcond failed by %s secs, fixed\n",
					    lfptoa(&lfpdelta, 9)));
				result = lfp_prev;
				L_ADDUF(&result, 1);
				sys_tsrounding++;
			}
		}
		lfp_prev = result;
		if (lamport_violated) 
			lamport_violated = FALSE;
	}
	LEAVE_GET_SYSTIME_CRITSEC();
	*now = result;
}