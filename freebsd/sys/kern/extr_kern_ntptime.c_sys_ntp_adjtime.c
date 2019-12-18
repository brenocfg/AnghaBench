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
struct timex {int modes; int status; scalar_t__ constant; scalar_t__ shift; long long freq; int offset; int precision; long tolerance; int ppsfreq; int jitter; int /*<<< orphan*/  stbcnt; int /*<<< orphan*/  jitcnt; int /*<<< orphan*/  errcnt; int /*<<< orphan*/  calcnt; int /*<<< orphan*/  stabil; int /*<<< orphan*/  esterror; int /*<<< orphan*/  maxerror; } ;
struct thread {int* td_retval; } ;
struct ntp_adjtime_args {scalar_t__ tp; } ;
typedef  int /*<<< orphan*/  ntv ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int L_GINT (long long) ; 
 int /*<<< orphan*/  L_LINT (long long,long) ; 
 long MAXFREQ ; 
 scalar_t__ MAXTC ; 
 int MOD_CLKA ; 
 int MOD_CLKB ; 
 int MOD_ESTERROR ; 
 int MOD_FREQUENCY ; 
 int MOD_MAXERROR ; 
 int MOD_MICRO ; 
 int MOD_NANO ; 
 int MOD_OFFSET ; 
 int MOD_PPSMAX ; 
 int MOD_STATUS ; 
 int MOD_TAI ; 
 int MOD_TIMECONST ; 
 int /*<<< orphan*/  NTP_LOCK () ; 
 int /*<<< orphan*/  NTP_UNLOCK () ; 
 scalar_t__ PPS_FAVG ; 
 scalar_t__ PPS_FAVGMAX ; 
 int /*<<< orphan*/  PRIV_NTP_ADJTIME ; 
 long SCALE_PPM ; 
 int STA_CLK ; 
 int STA_NANO ; 
 int STA_PLL ; 
 int STA_RONLY ; 
 int STA_UNSYNC ; 
 int TIME_ERROR ; 
 int TIME_OK ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hardupdate (int) ; 
 scalar_t__ ntp_is_time_error (int) ; 
 int /*<<< orphan*/  pps_calcnt ; 
 int /*<<< orphan*/  pps_errcnt ; 
 long long pps_freq ; 
 int /*<<< orphan*/  pps_jitcnt ; 
 int pps_jitter ; 
 scalar_t__ pps_shift ; 
 scalar_t__ pps_shiftmax ; 
 int /*<<< orphan*/  pps_stabil ; 
 int /*<<< orphan*/  pps_stbcnt ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_constant ; 
 int /*<<< orphan*/  time_esterror ; 
 long long time_freq ; 
 int /*<<< orphan*/  time_maxerror ; 
 long long time_offset ; 
 int time_precision ; 
 int time_state ; 
 int time_status ; 
 scalar_t__ time_tai ; 

int
sys_ntp_adjtime(struct thread *td, struct ntp_adjtime_args *uap)
{
	struct timex ntv;	/* temporary structure */
	long freq;		/* frequency ns/s) */
	int modes;		/* mode bits from structure */
	int error, retval;

	error = copyin((caddr_t)uap->tp, (caddr_t)&ntv, sizeof(ntv));
	if (error)
		return (error);

	/*
	 * Update selected clock variables - only the superuser can
	 * change anything. Note that there is no error checking here on
	 * the assumption the superuser should know what it is doing.
	 * Note that either the time constant or TAI offset are loaded
	 * from the ntv.constant member, depending on the mode bits. If
	 * the STA_PLL bit in the status word is cleared, the state and
	 * status words are reset to the initial values at boot.
	 */
	modes = ntv.modes;
	if (modes)
		error = priv_check(td, PRIV_NTP_ADJTIME);
	if (error != 0)
		return (error);
	NTP_LOCK();
	if (modes & MOD_MAXERROR)
		time_maxerror = ntv.maxerror;
	if (modes & MOD_ESTERROR)
		time_esterror = ntv.esterror;
	if (modes & MOD_STATUS) {
		if (time_status & STA_PLL && !(ntv.status & STA_PLL)) {
			time_state = TIME_OK;
			time_status = STA_UNSYNC;
#ifdef PPS_SYNC
			pps_shift = PPS_FAVG;
#endif /* PPS_SYNC */
		}
		time_status &= STA_RONLY;
		time_status |= ntv.status & ~STA_RONLY;
	}
	if (modes & MOD_TIMECONST) {
		if (ntv.constant < 0)
			time_constant = 0;
		else if (ntv.constant > MAXTC)
			time_constant = MAXTC;
		else
			time_constant = ntv.constant;
	}
	if (modes & MOD_TAI) {
		if (ntv.constant > 0) /* XXX zero & negative numbers ? */
			time_tai = ntv.constant;
	}
#ifdef PPS_SYNC
	if (modes & MOD_PPSMAX) {
		if (ntv.shift < PPS_FAVG)
			pps_shiftmax = PPS_FAVG;
		else if (ntv.shift > PPS_FAVGMAX)
			pps_shiftmax = PPS_FAVGMAX;
		else
			pps_shiftmax = ntv.shift;
	}
#endif /* PPS_SYNC */
	if (modes & MOD_NANO)
		time_status |= STA_NANO;
	if (modes & MOD_MICRO)
		time_status &= ~STA_NANO;
	if (modes & MOD_CLKB)
		time_status |= STA_CLK;
	if (modes & MOD_CLKA)
		time_status &= ~STA_CLK;
	if (modes & MOD_FREQUENCY) {
		freq = (ntv.freq * 1000LL) >> 16;
		if (freq > MAXFREQ)
			L_LINT(time_freq, MAXFREQ);
		else if (freq < -MAXFREQ)
			L_LINT(time_freq, -MAXFREQ);
		else {
			/*
			 * ntv.freq is [PPM * 2^16] = [us/s * 2^16]
			 * time_freq is [ns/s * 2^32]
			 */
			time_freq = ntv.freq * 1000LL * 65536LL;
		}
#ifdef PPS_SYNC
		pps_freq = time_freq;
#endif /* PPS_SYNC */
	}
	if (modes & MOD_OFFSET) {
		if (time_status & STA_NANO)
			hardupdate(ntv.offset);
		else
			hardupdate(ntv.offset * 1000);
	}

	/*
	 * Retrieve all clock variables. Note that the TAI offset is
	 * returned only by ntp_gettime();
	 */
	if (time_status & STA_NANO)
		ntv.offset = L_GINT(time_offset);
	else
		ntv.offset = L_GINT(time_offset) / 1000; /* XXX rounding ? */
	ntv.freq = L_GINT((time_freq / 1000LL) << 16);
	ntv.maxerror = time_maxerror;
	ntv.esterror = time_esterror;
	ntv.status = time_status;
	ntv.constant = time_constant;
	if (time_status & STA_NANO)
		ntv.precision = time_precision;
	else
		ntv.precision = time_precision / 1000;
	ntv.tolerance = MAXFREQ * SCALE_PPM;
#ifdef PPS_SYNC
	ntv.shift = pps_shift;
	ntv.ppsfreq = L_GINT((pps_freq / 1000LL) << 16);
	if (time_status & STA_NANO)
		ntv.jitter = pps_jitter;
	else
		ntv.jitter = pps_jitter / 1000;
	ntv.stabil = pps_stabil;
	ntv.calcnt = pps_calcnt;
	ntv.errcnt = pps_errcnt;
	ntv.jitcnt = pps_jitcnt;
	ntv.stbcnt = pps_stbcnt;
#endif /* PPS_SYNC */
	retval = ntp_is_time_error(time_status) ? TIME_ERROR : time_state;
	NTP_UNLOCK();

	error = copyout((caddr_t)&ntv, (caddr_t)uap->tp, sizeof(ntv));
	if (error == 0)
		td->td_retval[0] = retval;
	return (error);
}