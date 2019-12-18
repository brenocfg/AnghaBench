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
struct calendar {int monthday; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ DAY_NTP_STARTS ; 
 scalar_t__ NTP_TO_UNIX_DAYS ; 
 scalar_t__ ntpcal_date_to_rd (struct calendar*) ; 
 int /*<<< orphan*/  ntpcal_get_build_date (struct calendar*) ; 

int32_t
basedate_eval_buildstamp(void)
{
	struct calendar jd;
	int32_t		ed;
	
	if (!ntpcal_get_build_date(&jd))
		return NTP_TO_UNIX_DAYS;

	/* The time zone of the build stamp is unspecified; we remove
	 * one day to provide a certain slack. And in case somebody
	 * fiddled with the system clock, we make sure we do not go
	 * before the UNIX epoch (1970-01-01). It's probably not possible
	 * to do this to the clock on most systems, but there are other
	 * ways to tweak the build stamp.
	 */
	jd.monthday -= 1;
	ed = ntpcal_date_to_rd(&jd) - DAY_NTP_STARTS;
	return (ed < NTP_TO_UNIX_DAYS) ? NTP_TO_UNIX_DAYS : ed;
}