#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int l_ui; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  LFPTOD (TYPE_1__*,double) ; 
 scalar_t__ L_ISNEG (TYPE_1__*) ; 
 int /*<<< orphan*/  L_NEG (TYPE_1__*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  l_adj_systime (TYPE_1__*) ; 
 int step_systime (double) ; 

__attribute__((used)) static int
l_step_systime(
	l_fp *ts
	)
{
	double dtemp;

#ifdef SLEWALWAYS
#ifdef STEP_SLEW
	l_fp ftmp;
	int isneg;
	int n;

	if (debug)
		return 1;

	/*
	 * Take the absolute value of the offset
	 */
	ftmp = *ts;

	if (L_ISNEG(&ftmp)) {
		L_NEG(&ftmp);
		isneg = 1;
	} else
		isneg = 0;

	if (ftmp.l_ui >= 3) {		/* Step it and slew - we might win */
		LFPTOD(ts, dtemp);
		n = step_systime(dtemp);
		if (n == 0)
			return 0;
		if (isneg)		/* WTF! */
			ts->l_ui = ~0;
		else
			ts->l_ui = ~0;
	}
	/*
	 * Just add adjustment into the current offset.  The update
	 * routine will take care of bringing the system clock into
	 * line.
	 */
#endif
	if (debug)
		return 1;
#ifdef FORCE_NTPDATE_STEP
	LFPTOD(ts, dtemp);
	return step_systime(dtemp);
#else
	l_adj_systime(ts);
	return 1;
#endif
#else /* SLEWALWAYS */
	if (debug)
		return 1;
	LFPTOD(ts, dtemp);
	return step_systime(dtemp);
#endif	/* SLEWALWAYS */
}