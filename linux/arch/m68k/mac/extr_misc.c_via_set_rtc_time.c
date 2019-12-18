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
typedef  scalar_t__ time64_t ;
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CMD_WRITE (int /*<<< orphan*/ ) ; 
 int RTC_FLG_WRITE_PROTECT ; 
 scalar_t__ RTC_OFFSET ; 
 int /*<<< orphan*/  RTC_REG_SECONDS_0 ; 
 int /*<<< orphan*/  RTC_REG_SECONDS_1 ; 
 int /*<<< orphan*/  RTC_REG_SECONDS_2 ; 
 int /*<<< orphan*/  RTC_REG_SECONDS_3 ; 
 int /*<<< orphan*/  RTC_REG_WRITE_PROTECT ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 scalar_t__ mktime64 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_rtc_command (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void via_set_rtc_time(struct rtc_time *tm)
{
	union {
		__u8 cdata[4];
		__u32 idata;
	} data;
	__u8 temp;
	time64_t time;

	time = mktime64(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
	                tm->tm_hour, tm->tm_min, tm->tm_sec);

	/* Clear the write protect bit */

	temp = 0x55;
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_WRITE_PROTECT), &temp);

	data.idata = lower_32_bits(time + RTC_OFFSET);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_0), &data.cdata[3]);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_1), &data.cdata[2]);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_2), &data.cdata[1]);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_3), &data.cdata[0]);

	/* Set the write protect bit */

	temp = 0x55 | RTC_FLG_WRITE_PROTECT;
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_WRITE_PROTECT), &temp);
}