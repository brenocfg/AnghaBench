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
struct calendar {int dummy; } ;

/* Variables and functions */
 scalar_t__ DAY_NTP_STARTS ; 
 int /*<<< orphan*/  ntpcal_date_to_daysec (struct calendar const*) ; 
 scalar_t__ ntpcal_date_to_rd (struct calendar const*) ; 
 int /*<<< orphan*/  ntpcal_dayjoin (scalar_t__,int /*<<< orphan*/ ) ; 

vint64
ntpcal_date_to_ntp64(
	const struct calendar *jd
	)
{
	/*
	 * Convert date to NTP. Ignore yearday, use d/m/y only.
	 */
	return ntpcal_dayjoin(ntpcal_date_to_rd(jd) - DAY_NTP_STARTS,
			      ntpcal_date_to_daysec(jd));
}