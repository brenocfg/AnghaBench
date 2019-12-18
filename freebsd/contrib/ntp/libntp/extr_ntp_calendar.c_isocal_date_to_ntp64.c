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
typedef  int /*<<< orphan*/  vint64 ;
struct isodate {int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; scalar_t__ weekday; scalar_t__ week; scalar_t__ year; } ;
typedef  int int32_t ;

/* Variables and functions */
 int DAY_NTP_STARTS ; 
 int isocal_weeks_in_years (int) ; 
 int /*<<< orphan*/  ntpcal_dayjoin (int,int) ; 
 int ntpcal_etime_to_seconds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vint64
isocal_date_to_ntp64(
	const struct isodate *id
	)
{
	int32_t weeks, days, secs;

	weeks = isocal_weeks_in_years((int32_t)id->year - 1)
	      + (int32_t)id->week - 1;
	days = weeks * 7 + (int32_t)id->weekday;
	/* days is RDN of ISO date now */
	secs = ntpcal_etime_to_seconds(id->hour, id->minute, id->second);

	return ntpcal_dayjoin(days - DAY_NTP_STARTS, secs);
}