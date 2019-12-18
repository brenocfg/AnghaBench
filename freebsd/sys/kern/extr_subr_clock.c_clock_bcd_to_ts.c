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
struct timespec {int dummy; } ;
struct clocktime {int year; int mon; int day; int hour; int min; int sec; int /*<<< orphan*/  nsec; int /*<<< orphan*/  dow; } ;
struct bcd_clocktime {int year; int mon; int day; int hour; int min; int sec; scalar_t__ ispm; int /*<<< orphan*/  nsec; int /*<<< orphan*/  dow; } ;

/* Variables and functions */
 int EINVAL ; 
 int FROMBCD (int) ; 
 int clock_ct_to_ts (struct clocktime*,struct timespec*) ; 
 scalar_t__ ct_debug ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  validbcd (int) ; 

int
clock_bcd_to_ts(const struct bcd_clocktime *bct, struct timespec *ts, bool ampm)
{
	struct clocktime ct;
	int bcent, byear;

	/*
	 * Year may come in as 2-digit or 4-digit BCD.  Split the value into
	 * separate BCD century and year values for validation and conversion.
	 */
	bcent = bct->year >> 8;
	byear = bct->year & 0xff;

	/*
	 * Ensure that all values are valid BCD numbers, to avoid assertions in
	 * the BCD-to-binary conversion routines.  clock_ct_to_ts() will further
	 * validate the field ranges (such as 0 <= min <= 59) during conversion.
	 */
	if (!validbcd(bcent) || !validbcd(byear) || !validbcd(bct->mon) ||
	    !validbcd(bct->day) || !validbcd(bct->hour) ||
	    !validbcd(bct->min) || !validbcd(bct->sec)) {
		if (ct_debug)
			printf("clock_bcd_to_ts: bad BCD: "
			    "[%04x-%02x-%02x %02x:%02x:%02x]\n",
			    bct->year, bct->mon, bct->day,
			    bct->hour, bct->min, bct->sec);
		return (EINVAL);
	}

	ct.year = FROMBCD(byear) + FROMBCD(bcent) * 100;
	ct.mon  = FROMBCD(bct->mon);
	ct.day  = FROMBCD(bct->day);
	ct.hour = FROMBCD(bct->hour);
	ct.min  = FROMBCD(bct->min);
	ct.sec  = FROMBCD(bct->sec);
	ct.dow  = bct->dow;
	ct.nsec = bct->nsec;

	/* If asked to handle am/pm, convert from 12hr+pmflag to 24hr. */
	if (ampm) {
		if (ct.hour == 12)
			ct.hour = 0;
		if (bct->ispm)
			ct.hour += 12;
	}

	return (clock_ct_to_ts(&ct, ts));
}