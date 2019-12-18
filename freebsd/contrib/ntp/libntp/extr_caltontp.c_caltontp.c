#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lo; } ;
struct TYPE_5__ {TYPE_1__ d_s; } ;
typedef  TYPE_2__ vint64 ;
typedef  int /*<<< orphan*/  uint32_t ;
struct calendar {int month; int monthday; int yearday; int hour; scalar_t__ minute; scalar_t__ second; int /*<<< orphan*/  year; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ DAY_NTP_STARTS ; 
 scalar_t__ MINSPERHR ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ SECSPERMIN ; 
 scalar_t__ ntpcal_date_to_rd (struct calendar const*) ; 
 TYPE_2__ ntpcal_dayjoin (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntpcal_etime_to_seconds (int,scalar_t__,scalar_t__) ; 
 scalar_t__ ntpcal_year_to_ystart (int /*<<< orphan*/ ) ; 

uint32_t
caltontp(
	const struct calendar *jt
	)
{
	int32_t eraday;	/* CE Rata Die number	*/
	vint64  ntptime;/* resulting NTP time	*/

	REQUIRE(jt != NULL);

	REQUIRE(jt->month <= 13);	/* permit month 0..13! */
	REQUIRE(jt->monthday <= 32);
	REQUIRE(jt->yearday <= 366);
	REQUIRE(jt->hour <= 24);
	REQUIRE(jt->minute <= MINSPERHR);
	REQUIRE(jt->second <= SECSPERMIN);

	/*
	 * First convert the date to he corresponding RataDie
	 * number. If yearday is not zero, assume that it contains a
	 * useable value and avoid all calculations involving month
	 * and day-of-month. Do a full evaluation otherwise.
	 */
	if (jt->yearday)
		eraday = ntpcal_year_to_ystart(jt->year)
		       + jt->yearday - 1;
	else
		eraday = ntpcal_date_to_rd(jt);

	ntptime = ntpcal_dayjoin(eraday - DAY_NTP_STARTS,
				 ntpcal_etime_to_seconds(jt->hour, jt->minute,
							 jt->second));
	return ntptime.d_s.lo;
}