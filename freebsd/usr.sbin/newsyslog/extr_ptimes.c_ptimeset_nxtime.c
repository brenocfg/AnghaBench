#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tm_mon; int tm_mday; int tm_year; int tm_isdst; } ;
struct ptime_data {int tmspec; int tsecs; TYPE_1__ tm; } ;

/* Variables and functions */
 int SECS_PER_HOUR ; 
 int TSPEC_DAYOFMONTH ; 
 int TSPEC_DAYOFWEEK ; 
 int TSPEC_HOUROFDAY ; 
 int TSPEC_LDAYOFMONTH ; 
 int TSPEC_MONTHOFYEAR ; 
 int TSPEC_YEAR ; 
 int days_pmonth (int,int) ; 
 TYPE_1__* localtime (int*) ; 
 int mktime (TYPE_1__*) ; 
 int /*<<< orphan*/  ptime_adjust4dst (struct ptime_data*,struct ptime_data*) ; 

int
ptimeset_nxtime(struct ptime_data *ptime)
{
	int moredays, tdpm, tmon, tyear;
	struct ptime_data nextmatch;

	if (ptime == NULL)
		return (-1);

	/*
	 * Changes are not made to the given time until after all
	 * of the calculations have been successful.
	 */
	nextmatch = *ptime;
	/*
	 * If the user specified a year and we're already past that
	 * time, then there will never be another one!
	 */
	if (ptime->tmspec & TSPEC_YEAR)
		return (-1);

	/*
	 * The caller gave us a time in the past.  Calculate how much
	 * time is needed to go from that valid rotate time to the
	 * next valid rotate time.  We only need to get to the nearest
	 * hour, because newsyslog is only run once per hour.
	 */
	moredays = 0;
	if (ptime->tmspec & TSPEC_MONTHOFYEAR) {
		/* Special case: Feb 29th does not happen every year. */
		if (ptime->tm.tm_mon == 1 && ptime->tm.tm_mday == 29) {
			nextmatch.tm.tm_year += 4;
			if (days_pmonth(1, nextmatch.tm.tm_year) < 29)
				nextmatch.tm.tm_year += 4;
		} else {
			nextmatch.tm.tm_year += 1;
		}
		nextmatch.tm.tm_isdst = -1;
		nextmatch.tsecs = mktime(&nextmatch.tm);

	} else if (ptime->tmspec & TSPEC_LDAYOFMONTH) {
		/*
		 * Need to get to the last day of next month.  Origtm is
		 * already at the last day of this month, so just add to
		 * it number of days in the next month.
		 */
		if (ptime->tm.tm_mon < 11)
			moredays = days_pmonth(ptime->tm.tm_mon + 1,
			    ptime->tm.tm_year);
		else
			moredays = days_pmonth(0, ptime->tm.tm_year + 1);

	} else if (ptime->tmspec & TSPEC_DAYOFMONTH) {
		/* Jump to the same day in the next month */
		moredays = days_pmonth(ptime->tm.tm_mon, ptime->tm.tm_year);
		/*
		 * In some cases, the next month may not *have* the
		 * desired day-of-the-month.  If that happens, then
		 * move to the next month that does have enough days.
		 */
		tmon = ptime->tm.tm_mon;
		tyear = ptime->tm.tm_year;
		for (;;) {
			if (tmon < 11)
				tmon += 1;
			else {
				tmon = 0;
				tyear += 1;
			}
			tdpm = days_pmonth(tmon, tyear);
			if (tdpm >= ptime->tm.tm_mday)
				break;
			moredays += tdpm;
		}

	} else if (ptime->tmspec & TSPEC_DAYOFWEEK) {
		moredays = 7;
	} else if (ptime->tmspec & TSPEC_HOUROFDAY) {
		moredays = 1;
	}

	if (moredays != 0) {
		nextmatch.tsecs += SECS_PER_HOUR * 24 * moredays;
		nextmatch.tm = *(localtime(&nextmatch.tsecs));
	}

	/*
	 * The new time will need to be adjusted if the setting of
	 * daylight-saving has changed between the two times.
	 */
	ptime_adjust4dst(&nextmatch, ptime);

	/* Everything worked.  Update the given time and return. */
	*ptime = nextmatch;
	return (0);
}