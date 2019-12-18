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
typedef  int uint16_t ;
struct timestamp {int month; int minute; int hour; int day; int centisec; int hund_usec; int /*<<< orphan*/  type_tz; scalar_t__ usec; scalar_t__ second; int /*<<< orphan*/  year; } ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
typedef  int int16_t ;

/* Variables and functions */
 int le16toh (int /*<<< orphan*/ ) ; 
 int** mon_lens ; 
 int udf_isaleapyear (int) ; 

__attribute__((used)) static void
udf_timetotimespec(struct timestamp *time, struct timespec *t)
{
	int i, lpyear, daysinyear, year, startyear;
	union {
		uint16_t	u_tz_offset;
		int16_t		s_tz_offset;
	} tz;

	/*
	 * DirectCD seems to like using bogus year values.
	 * Don't trust time->month as it will be used for an array index.
	 */
	year = le16toh(time->year);
	if (year < 1970 || time->month < 1 || time->month > 12) {
		t->tv_sec = 0;
		t->tv_nsec = 0;
		return;
	}

	/* Calculate the time and day */
	t->tv_sec = time->second;
	t->tv_sec += time->minute * 60;
	t->tv_sec += time->hour * 3600;
	t->tv_sec += (time->day - 1) * 3600 * 24;

	/* Calculate the month */
	lpyear = udf_isaleapyear(year);
	t->tv_sec += mon_lens[lpyear][time->month - 1] * 3600 * 24;

	/* Speed up the calculation */
	startyear = 1970;
	if (year > 2009) {
		t->tv_sec += 1262304000;
		startyear += 40;
	} else if (year > 1999) {
		t->tv_sec += 946684800;
		startyear += 30;
	} else if (year > 1989) {
		t->tv_sec += 631152000;
		startyear += 20;
	} else if (year > 1979) {
		t->tv_sec += 315532800;
		startyear += 10;
	}

	daysinyear = (year - startyear) * 365;
	for (i = startyear; i < year; i++)
		daysinyear += udf_isaleapyear(i);
	t->tv_sec += daysinyear * 3600 * 24;

	/* Calculate microseconds */
	t->tv_nsec = time->centisec * 10000 + time->hund_usec * 100 +
	    time->usec;

	/*
	 * Calculate the time zone.  The timezone is 12 bit signed 2's
	 * complement, so we gotta do some extra magic to handle it right.
	 */
	tz.u_tz_offset = le16toh(time->type_tz);
	tz.u_tz_offset &= 0x0fff;
	if (tz.u_tz_offset & 0x0800)
		tz.u_tz_offset |= 0xf000;	/* extend the sign to 16 bits */
	if ((le16toh(time->type_tz) & 0x1000) && (tz.s_tz_offset != -2047))
		t->tv_sec -= tz.s_tz_offset * 60;

	return;
}