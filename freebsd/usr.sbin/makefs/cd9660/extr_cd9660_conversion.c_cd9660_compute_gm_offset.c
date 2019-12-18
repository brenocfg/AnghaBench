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
typedef  int /*<<< orphan*/  time_t ;
struct tm {scalar_t__ tm_year; int tm_yday; int tm_hour; int tm_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 

__attribute__((used)) static char
cd9660_compute_gm_offset(time_t tim)
{
	struct tm t, gm;

	(void)localtime_r(&tim, &t);
	(void)gmtime_r(&tim, &gm);
	gm.tm_year -= t.tm_year;
	gm.tm_yday -= t.tm_yday;
	gm.tm_hour -= t.tm_hour;
	gm.tm_min  -= t.tm_min;
	if (gm.tm_year < 0)
		gm.tm_yday = -1;
	else if (gm.tm_year > 0)
		gm.tm_yday = 1;

	return (char)(-(gm.tm_min + 60* (24 * gm.tm_yday + gm.tm_hour)) / 15);
}