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
struct rtc_time {int tm_year; void* tm_sec; void* tm_min; void* tm_hour; void* tm_mday; void* tm_mon; } ;
struct TYPE_2__ {scalar_t__ ctrl; int /*<<< orphan*/  bcd_sec; int /*<<< orphan*/  bcd_min; int /*<<< orphan*/  bcd_hr; int /*<<< orphan*/  bcd_dom; int /*<<< orphan*/  bcd_mth; int /*<<< orphan*/  bcd_year; } ;

/* Variables and functions */
 scalar_t__ RTC_READ ; 
 void* bcd2int (int /*<<< orphan*/ ) ; 
 TYPE_1__* rtc ; 

int mvme16x_hwclk(int op, struct rtc_time *t)
{
#warning check me!
	if (!op) {
		rtc->ctrl = RTC_READ;
		t->tm_year = bcd2int (rtc->bcd_year);
		t->tm_mon  = bcd2int(rtc->bcd_mth) - 1;
		t->tm_mday = bcd2int (rtc->bcd_dom);
		t->tm_hour = bcd2int (rtc->bcd_hr);
		t->tm_min  = bcd2int (rtc->bcd_min);
		t->tm_sec  = bcd2int (rtc->bcd_sec);
		rtc->ctrl = 0;
		if (t->tm_year < 70)
			t->tm_year += 100;
	}
	return 0;
}