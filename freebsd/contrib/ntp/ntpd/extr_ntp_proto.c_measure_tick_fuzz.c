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
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  DTOLFP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LFPTOD (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ L_ISGT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L_SUB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAXLOOPS ; 
 double MAXSTEP ; 
 int MINCHANGES ; 
 int /*<<< orphan*/  MINSTEP ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 long max (long,long) ; 
 double min (double,double) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_sys_fuzz (double) ; 

double
measure_tick_fuzz(void)
{
	l_fp	minstep;	/* MINSTEP as l_fp */
	l_fp	val;		/* current seconds fraction */
	l_fp	last;		/* last seconds fraction */
	l_fp	ldiff;		/* val - last */
	double	tick;		/* computed tick value */
	double	diff;
	long	repeats;
	long	max_repeats;
	int	changes;
	int	i;		/* log2 precision */

	tick = MAXSTEP;
	max_repeats = 0;
	repeats = 0;
	changes = 0;
	DTOLFP(MINSTEP, &minstep);
	get_systime(&last);
	for (i = 0; i < MAXLOOPS && changes < MINCHANGES; i++) {
		get_systime(&val);
		ldiff = val;
		L_SUB(&ldiff, &last);
		last = val;
		if (L_ISGT(&ldiff, &minstep)) {
			max_repeats = max(repeats, max_repeats);
			repeats = 0;
			changes++;
			LFPTOD(&ldiff, diff);
			tick = min(diff, tick);
		} else {
			repeats++;
		}
	}
	if (changes < MINCHANGES) {
		msyslog(LOG_ERR, "Fatal error: precision could not be measured (MINSTEP too large?)");
		exit(1);
	}

	if (0 == max_repeats) {
		set_sys_fuzz(tick);
	} else {
		set_sys_fuzz(tick / max_repeats);
	}

	return tick;
}