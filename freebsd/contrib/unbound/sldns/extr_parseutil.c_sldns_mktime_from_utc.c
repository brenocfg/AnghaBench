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
typedef  int time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 scalar_t__ is_leap_year (int) ; 
 int leap_days (int,int) ; 
 scalar_t__* mdays ; 

time_t
sldns_mktime_from_utc(const struct tm *tm)
{
	int year = 1900 + tm->tm_year;
	time_t days = 365 * ((time_t) year - 1970) + leap_days(1970, year);
	time_t hours;
	time_t minutes;
	time_t seconds;
	int i;

	for (i = 0; i < tm->tm_mon; ++i) {
		days += mdays[i];
	}
	if (tm->tm_mon > 1 && is_leap_year(year)) {
		++days;
	}
	days += tm->tm_mday - 1;

	hours = days * 24 + tm->tm_hour;
	minutes = hours * 60 + tm->tm_min;
	seconds = minutes * 60 + tm->tm_sec;

	return seconds;
}