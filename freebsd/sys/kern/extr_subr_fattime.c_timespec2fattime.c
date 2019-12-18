#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int time_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_2__ {unsigned int days; scalar_t__ coded; } ;

/* Variables and functions */
 int DAY ; 
 int FEB ; 
 int LYC ; 
 unsigned int T1980 ; 
 TYPE_1__* mtab ; 
 scalar_t__ utc_offset () ; 

void
timespec2fattime(const struct timespec *tsp, int utc, uint16_t *ddp,
    uint16_t *dtp, uint8_t *dhp)
{
	time_t t1;
	unsigned t2, l, m;

	t1 = tsp->tv_sec;
	if (!utc)
		t1 -= utc_offset();

	if (dhp != NULL)
		*dhp = (tsp->tv_sec & 1) * 100 + tsp->tv_nsec / 10000000;
	if (dtp != NULL) {
		*dtp = (t1 / 2) % 30;
		*dtp |= ((t1 / 60) % 60) << 5;
		*dtp |= ((t1 / 3600) % 24) << 11;
	}
	if (ddp != NULL) {
		t2 = t1 / DAY;
		if (t2 < T1980) {
			/* Impossible date, truncate to 1980-01-01 */
			*ddp = 0x0021;
		} else {
			t2 -= T1980;

			/*
			 * 2100 is not a leap year.
			 * XXX: a 32 bit time_t can not get us here.
			 */
			if (t2 >= ((2100 - 1980) / 4 * LYC + FEB))
				t2++;

			/* Account for full leapyear cycles */
			l = t2 / LYC;
			*ddp = (l * 4) << 9;
			t2 -= l * LYC;

			/* Find approximate table entry */
			m = t2 / 32;

			/* Find correct table entry */
			while (m < 47 && mtab[m + 1].days <= t2)
				m++;

			/* Get year + month from the table */
			*ddp += mtab[m].coded;

			/* And apply the day in the month */
			t2 -= mtab[m].days - 1;
			*ddp |= t2;
		}
	}
}