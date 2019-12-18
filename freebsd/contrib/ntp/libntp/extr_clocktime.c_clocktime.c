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
typedef  int u_long ;
typedef  int u_int32 ;
typedef  int int32 ;

/* Variables and functions */
 int CLOSETIME ; 
 int HRSPERDAY ; 
 int MINSPERHR ; 
 int NEARTIME ; 
 int SECSPERMIN ; 
 int ntp_to_year (int) ; 
 int year_to_ntp (int) ; 

int
clocktime(
	int	yday	 ,	/* day-of-year */
	int	hour	 ,	/* hour of day */
	int	minute	 ,	/* minute of hour */
	int	second	 ,	/* second of minute */
	int	tzoff	 ,	/* hours west of GMT */
	u_int32 rec_ui	 ,	/* pivot value */
	u_long *yearstart,	/* cached start-of-year, should be fixed to u_int32 */
	u_int32 *ts_ui	 )	/* effective time stamp */
{
	u_int32 ystt[3];	/* year start */
	u_int32 test[3];	/* result time stamp */
	u_int32 diff[3];	/* abs difference to receive */
	int32 y, tmp, idx, min;
	
	/*
	 * Compute the offset into the year in seconds.	 Note that
	 * this could come out to be a negative number.
	 */
	tmp = ((int32)second +
	       SECSPERMIN * ((int32)minute +
			     MINSPERHR * ((int32)hour + (int32)tzoff +
					  HRSPERDAY * ((int32)yday - 1))));
	/*
	 * Based on the cached year start, do a first attempt. Be
	 * happy and return if this gets us better than NEARTIME to
	 * the receive time stamp. Do this only if the cached year
	 * start is not zero, which will not happen after 1900 for the
	 * next few thousand years.
	 */
	if (*yearstart) {
		/* -- get time stamp of potential solution */
		test[0] = (u_int32)(*yearstart) + tmp;
		/* -- calc absolute difference to receive time */
		diff[0] = test[0] - rec_ui;
		if (diff[0] >= 0x80000000u)
			diff[0] = ~diff[0] + 1;
		/* -- can't get closer if diff < NEARTIME */
		if (diff[0] < NEARTIME) {
			*ts_ui = test[0];
			return diff[0] < CLOSETIME;
		}
	}

	/*
	 * Now the dance begins. Based on the receive time stamp and
	 * the seconds offset in 'tmp', we make an educated guess
	 * about the year to start with. This takes us on the spot
	 * with a fuzz of +/-1 year.
	 *
	 * We calculate the effective timestamps for the three years
	 * around the guess and select the entry with the minimum
	 * absolute difference to the receive time stamp.
	 */
	y = ntp_to_year(rec_ui - tmp);
	for (idx = 0; idx < 3; idx++) {
		/* -- get year start of potential solution */
		ystt[idx] = year_to_ntp(y + idx - 1);
		/* -- get time stamp of potential solution */
		test[idx] = ystt[idx] + tmp;
		/* -- calc absolute difference to receive time */
		diff[idx] = test[idx] - rec_ui;
		if (diff[idx] >= 0x80000000u)
			diff[idx] = ~diff[idx] + 1;
	}
	/* -*- assume current year fits best, then search best fit */
	for (min = 1, idx = 0; idx < 3; idx++)
		if (diff[idx] < diff[min])
			min = idx;
	/* -*- store results and update year start */
	*ts_ui	   = test[min];
	*yearstart = ystt[min];

	/* -*- tell if we could get into CLOSETIME*/
	return diff[min] < CLOSETIME;
}