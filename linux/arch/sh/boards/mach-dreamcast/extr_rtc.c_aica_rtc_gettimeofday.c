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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ time64_t ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICA_RTC_SECS_H ; 
 int /*<<< orphan*/  AICA_RTC_SECS_L ; 
 unsigned long TWENTY_YEARS ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,struct rtc_time*) ; 

__attribute__((used)) static int aica_rtc_gettimeofday(struct device *dev, struct rtc_time *tm)
{
	unsigned long val1, val2;
	time64_t t;

	do {
		val1 = ((__raw_readl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(__raw_readl(AICA_RTC_SECS_L) & 0xffff);

		val2 = ((__raw_readl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(__raw_readl(AICA_RTC_SECS_L) & 0xffff);
	} while (val1 != val2);

	/* normalize to 1970..2106 time range */
	t = (u32)(val1 - TWENTY_YEARS);

	rtc_time64_to_tm(t, tm);

	return 0;
}