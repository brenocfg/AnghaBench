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
struct clocktime {int hour; int year; int mon; int day; int min; int sec; int /*<<< orphan*/  nsec; int /*<<< orphan*/  dow; } ;
struct bcd_clocktime {int ispm; int year; int mon; int day; int hour; int min; int sec; int /*<<< orphan*/  nsec; int /*<<< orphan*/  dow; } ;

/* Variables and functions */
 int TOBCD (int) ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec const*,struct clocktime*) ; 

void
clock_ts_to_bcd(const struct timespec *ts, struct bcd_clocktime *bct, bool ampm)
{
	struct clocktime ct;

	clock_ts_to_ct(ts, &ct);

	/* If asked to handle am/pm, convert from 24hr to 12hr+pmflag. */
	bct->ispm = false;
	if (ampm) {
		if (ct.hour >= 12) {
			ct.hour -= 12;
			bct->ispm = true;
		}
		if (ct.hour == 0)
			ct.hour = 12;
	}

	bct->year = TOBCD(ct.year % 100) | (TOBCD(ct.year / 100) << 8);
	bct->mon  = TOBCD(ct.mon);
	bct->day  = TOBCD(ct.day);
	bct->hour = TOBCD(ct.hour);
	bct->min  = TOBCD(ct.min);
	bct->sec  = TOBCD(ct.sec);
	bct->dow  = ct.dow;
	bct->nsec = ct.nsec;
}