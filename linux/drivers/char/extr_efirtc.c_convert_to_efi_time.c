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
struct rtc_time {scalar_t__ tm_isdst; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_3__ {int /*<<< orphan*/  timezone; int /*<<< orphan*/  daylight; scalar_t__ nanosecond; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; scalar_t__ month; scalar_t__ year; } ;
typedef  TYPE_1__ efi_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_ISDST ; 
 int /*<<< orphan*/  EFI_UNSPECIFIED_TIMEZONE ; 

__attribute__((used)) static void
convert_to_efi_time(struct rtc_time *wtime, efi_time_t *eft)
{

	eft->year	= wtime->tm_year + 1900;
	eft->month	= wtime->tm_mon + 1; 
	eft->day	= wtime->tm_mday;
	eft->hour	= wtime->tm_hour;
	eft->minute	= wtime->tm_min;
	eft->second 	= wtime->tm_sec;
	eft->nanosecond = 0; 
	eft->daylight	= wtime->tm_isdst ? EFI_ISDST: 0;
	eft->timezone	= EFI_UNSPECIFIED_TIMEZONE;
}