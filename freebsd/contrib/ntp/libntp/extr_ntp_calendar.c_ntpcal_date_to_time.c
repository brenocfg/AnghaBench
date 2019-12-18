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
typedef  int /*<<< orphan*/  time_t ;
struct calendar {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ DAY_UNIX_STARTS ; 
 scalar_t__ ntpcal_date_to_daysec (struct calendar const*) ; 
 scalar_t__ ntpcal_date_to_rd (struct calendar const*) ; 
 int /*<<< orphan*/  ntpcal_dayjoin (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vint64_to_time (int /*<<< orphan*/ *) ; 

time_t
ntpcal_date_to_time(
	const struct calendar *jd
	)
{
	vint64  join;
	int32_t days, secs;

	days = ntpcal_date_to_rd(jd) - DAY_UNIX_STARTS;
	secs = ntpcal_date_to_daysec(jd);
	join = ntpcal_dayjoin(days, secs);

	return vint64_to_time(&join);
}