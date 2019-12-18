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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; scalar_t__ tm_wday; } ;
struct TYPE_2__ {int msr; int t0cr_rtmr; void* bcd_dow; void* bcd_year; void* bcd_mth; void* bcd_dom; void* bcd_hr; void* bcd_min; void* bcd_sec; scalar_t__ bcd_tenms; } ;
typedef  TYPE_1__* RtcPtr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BVME_RTC_BASE ; 
 scalar_t__ bcd2bin (void*) ; 
 void* bin2bcd (int) ; 

int bvme6000_hwclk(int op, struct rtc_time *t)
{
	volatile RtcPtr_t rtc = (RtcPtr_t)BVME_RTC_BASE;
	unsigned char msr = rtc->msr & 0xc0;

	rtc->msr = 0x40;	/* Ensure clock and real-time-mode-register
				 * are accessible */
	if (op)
	{	/* Write.... */
		rtc->t0cr_rtmr = t->tm_year%4;
		rtc->bcd_tenms = 0;
		rtc->bcd_sec = bin2bcd(t->tm_sec);
		rtc->bcd_min = bin2bcd(t->tm_min);
		rtc->bcd_hr  = bin2bcd(t->tm_hour);
		rtc->bcd_dom = bin2bcd(t->tm_mday);
		rtc->bcd_mth = bin2bcd(t->tm_mon + 1);
		rtc->bcd_year = bin2bcd(t->tm_year%100);
		if (t->tm_wday >= 0)
			rtc->bcd_dow = bin2bcd(t->tm_wday+1);
		rtc->t0cr_rtmr = t->tm_year%4 | 0x08;
	}
	else
	{	/* Read....  */
		do {
			t->tm_sec  = bcd2bin(rtc->bcd_sec);
			t->tm_min  = bcd2bin(rtc->bcd_min);
			t->tm_hour = bcd2bin(rtc->bcd_hr);
			t->tm_mday = bcd2bin(rtc->bcd_dom);
			t->tm_mon  = bcd2bin(rtc->bcd_mth)-1;
			t->tm_year = bcd2bin(rtc->bcd_year);
			if (t->tm_year < 70)
				t->tm_year += 100;
			t->tm_wday = bcd2bin(rtc->bcd_dow)-1;
		} while (t->tm_sec != bcd2bin(rtc->bcd_sec));
	}

	rtc->msr = msr;

	return 0;
}