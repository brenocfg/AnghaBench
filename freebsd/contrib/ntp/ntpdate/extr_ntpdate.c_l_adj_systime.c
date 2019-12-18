#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_9__ {scalar_t__ l_ui; scalar_t__ l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 scalar_t__ ADJ_MAXOVERSHOOT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  L_ADD (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ L_ISNEG (TYPE_1__*) ; 
 int /*<<< orphan*/  L_NEG (TYPE_1__*) ; 
 int /*<<< orphan*/  L_RSHIFTU (TYPE_1__*) ; 
 int /*<<< orphan*/  TSTOTV (TYPE_1__*,struct timeval*) ; 
 scalar_t__ adjtime (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
l_adj_systime(
	l_fp *ts
	)
{
	struct timeval adjtv, oadjtv;
	int isneg = 0;
	l_fp offset;
#ifndef STEP_SLEW
	l_fp overshoot;
#endif

	/*
	 * Take the absolute value of the offset
	 */
	offset = *ts;
	if (L_ISNEG(&offset)) {
		isneg = 1;
		L_NEG(&offset);
	}

#ifndef STEP_SLEW
	/*
	 * Calculate the overshoot.  XXX N.B. This code *knows*
	 * ADJ_OVERSHOOT is 1/2.
	 */
	overshoot = offset;
	L_RSHIFTU(&overshoot);
	if (overshoot.l_ui != 0 || (overshoot.l_uf > ADJ_MAXOVERSHOOT)) {
		overshoot.l_ui = 0;
		overshoot.l_uf = ADJ_MAXOVERSHOOT;
	}
	L_ADD(&offset, &overshoot);
#endif
	TSTOTV(&offset, &adjtv);

	if (isneg) {
		adjtv.tv_sec = -adjtv.tv_sec;
		adjtv.tv_usec = -adjtv.tv_usec;
	}

	if (!debug && (adjtv.tv_usec != 0)) {
		/* A time correction needs to be applied. */
#if !defined SYS_WINNT && !defined SYS_CYGWIN32
		/* Slew the time on systems that support this. */
		if (adjtime(&adjtv, &oadjtv) < 0) {
			msyslog(LOG_ERR, "Can't adjust the time of day: %m");
			exit(1);
		}
#else	/* SYS_WINNT or SYS_CYGWIN32 is defined */
		/*
		 * The NT SetSystemTimeAdjustment() call achieves slewing by
		 * changing the clock frequency. This means that we cannot specify
		 * it to slew the clock by a definite amount and then stop like
		 * the Unix adjtime() routine. We can technically adjust the clock
		 * frequency, have ntpdate sleep for a while, and then wake
		 * up and reset the clock frequency, but this might cause some
		 * grief if the user attempts to run ntpd immediately after
		 * ntpdate and the socket is in use.
		 */
		printf("\nSlewing the system time is not supported on Windows. Use the -b option to step the time.\n");
#endif	/* defined SYS_WINNT || defined SYS_CYGWIN32 */
	}
	return 1;
}