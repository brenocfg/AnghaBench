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
struct timeval {long tv_sec; long tv_usec; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int TRUE ; 
 scalar_t__ adjtime (struct timeval*,struct timeval*) ; 
 scalar_t__ allow_panic ; 
 scalar_t__ enable_panic_check ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 double sys_fuzz ; 
 double sys_residual ; 
 double sys_tick ; 

int				/* 0 okay, 1 error */
adj_systime(
	double now		/* adjustment (s) */
	)
{
	struct timeval adjtv;	/* new adjustment */
	struct timeval oadjtv;	/* residual adjustment */
	double	quant;		/* quantize to multiples of */
	double	dtemp;
	long	ticks;
	int	isneg = 0;

	/*
	 * The Windows port adj_systime() depends on being called each
	 * second even when there's no additional correction, to allow
	 * emulation of adjtime() behavior on top of an API that simply
	 * sets the current rate.  This POSIX implementation needs to
	 * ignore invocations with zero correction, otherwise ongoing
	 * EVNT_NSET adjtime() can be aborted by a tiny adjtime()
	 * triggered by sys_residual.
	 */
	if (0. == now) {
		if (enable_panic_check && allow_panic) {
			msyslog(LOG_ERR, "adj_systime: allow_panic is TRUE!");
			INSIST(!allow_panic);
		}
		return TRUE;
	}

	/*
	 * Most Unix adjtime() implementations adjust the system clock
	 * in microsecond quanta, but some adjust in 10-ms quanta. We
	 * carefully round the adjustment to the nearest quantum, then
	 * adjust in quanta and keep the residue for later.
	 */
	dtemp = now + sys_residual;
	if (dtemp < 0) {
		isneg = 1;
		dtemp = -dtemp;
	}
	adjtv.tv_sec = (long)dtemp;
	dtemp -= adjtv.tv_sec;
	if (sys_tick > sys_fuzz)
		quant = sys_tick;
	else
		quant = 1e-6;
	ticks = (long)(dtemp / quant + .5);
	adjtv.tv_usec = (long)(ticks * quant * 1.e6 + .5);
	/* The rounding in the conversions could us push over the
	 * limits: make sure the result is properly normalised!
	 * note: sign comes later, all numbers non-negative here.
	 */
	if (adjtv.tv_usec >= 1000000) {
		adjtv.tv_sec  += 1;
		adjtv.tv_usec -= 1000000;
		dtemp         -= 1.;
	}
	/* set the new residual with leftover from correction */
	sys_residual = dtemp - adjtv.tv_usec * 1.e-6;

	/*
	 * Convert to signed seconds and microseconds for the Unix
	 * adjtime() system call. Note we purposely lose the adjtime()
	 * leftover.
	 */
	if (isneg) {
		adjtv.tv_sec = -adjtv.tv_sec;
		adjtv.tv_usec = -adjtv.tv_usec;
		sys_residual = -sys_residual;
	}
	if (adjtv.tv_sec != 0 || adjtv.tv_usec != 0) {
		if (adjtime(&adjtv, &oadjtv) < 0) {
			msyslog(LOG_ERR, "adj_systime: %m");
			if (enable_panic_check && allow_panic) {
				msyslog(LOG_ERR, "adj_systime: allow_panic is TRUE!");
			}
			return FALSE;
		}
	}
	if (enable_panic_check && allow_panic) {
		msyslog(LOG_ERR, "adj_systime: allow_panic is TRUE!");
	}
	return TRUE;
}