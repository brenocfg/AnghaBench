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
typedef  int /*<<< orphan*/  tmd_tomorrow ;
typedef  int /*<<< orphan*/  tmd_today ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_yday; scalar_t__ tm_mon; } ;

/* Variables and functions */
 int DAYSPERLEAPYEAR ; 
 int DAYSPERYEAR ; 
 int EPOCH ; 
 int FHOURSPERDAY ; 
 int FSECSPERHOUR ; 
 int FSECSPERMINUTE ; 
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ isleap (int) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 double potm (double) ; 
 double potm_minute (double,int) ; 

void
fpom(int year, double utcoffset, double *ffms, double *fnms)
{
	time_t tt;
	struct tm GMT, tmd_today, tmd_tomorrow;
	double days_today, days_tomorrow, today, tomorrow;
	int cnt, d;
	int yeardays;
	int olddir, newdir;
	double *pfnms, *pffms, t;

	pfnms = fnms;
	pffms = ffms;

	/*
	 * We take the phase of the moon one second before and one second
	 * after midnight.
	 */
	memset(&tmd_today, 0, sizeof(tmd_today));
	tmd_today.tm_year = year - 1900;
	tmd_today.tm_mon = 0;
	tmd_today.tm_mday = -1;		/* 31 December */
	tmd_today.tm_hour = 23;
	tmd_today.tm_min = 59;
	tmd_today.tm_sec = 59;
	memset(&tmd_tomorrow, 0, sizeof(tmd_tomorrow));
	tmd_tomorrow.tm_year = year - 1900;
	tmd_tomorrow.tm_mon = 0;
	tmd_tomorrow.tm_mday = 0;	/* 01 January */
	tmd_tomorrow.tm_hour = 0;
	tmd_tomorrow.tm_min = 0;
	tmd_tomorrow.tm_sec = 1;

	tt = mktime(&tmd_today);
	gmtime_r(&tt, &GMT);
	yeardays = 0;
	for (cnt = EPOCH; cnt < GMT.tm_year; ++cnt)
		yeardays += isleap(1900 + cnt) ? DAYSPERLEAPYEAR : DAYSPERYEAR;
	days_today = (GMT.tm_yday + 1) + ((GMT.tm_hour +
	    (GMT.tm_min / FSECSPERMINUTE) + (GMT.tm_sec / FSECSPERHOUR)) /
	    FHOURSPERDAY);
	days_today += yeardays;

	tt = mktime(&tmd_tomorrow);
	gmtime_r(&tt, &GMT);
	yeardays = 0;
	for (cnt = EPOCH; cnt < GMT.tm_year; ++cnt)
		yeardays += isleap(1900 + cnt) ? DAYSPERLEAPYEAR : DAYSPERYEAR;
	days_tomorrow = (GMT.tm_yday + 1) + ((GMT.tm_hour +
	    (GMT.tm_min / FSECSPERMINUTE) + (GMT.tm_sec / FSECSPERHOUR)) /
	    FHOURSPERDAY);
	days_tomorrow += yeardays;

	today = potm(days_today);		/* 30 December 23:59:59 */
	tomorrow = potm(days_tomorrow);		/* 31 December 00:00:01 */
	olddir = today > tomorrow ? -1 : +1;

	yeardays = 1 + (isleap(year) ? DAYSPERLEAPYEAR : DAYSPERYEAR); /* reuse */
	for (d = 0; d <= yeardays; d++) {
		today = potm(days_today);
		tomorrow = potm(days_tomorrow);
		newdir = today > tomorrow ? -1 : +1;
		if (olddir != newdir) {
			t = potm_minute(days_today - 1, olddir) +
			     utcoffset / FHOURSPERDAY;
			if (olddir == -1 && newdir == +1) {
				*pfnms = d - 1 + t;
				pfnms++;
			} else if (olddir == +1 && newdir == -1) {
				*pffms = d - 1 + t;
				pffms++;
			}
		}
		olddir = newdir;
		days_today++;
		days_tomorrow++;
	}
	*pffms = -1;
	*pfnms = -1;
}