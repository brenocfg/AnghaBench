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
typedef  scalar_t__ time_t ;
struct tm {size_t tm_wday; size_t tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; } ;
struct TYPE_3__ {int offset; scalar_t__ time; } ;
typedef  TYPE_1__ git_time ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * month_names ; 
 int /*<<< orphan*/ * p_gmtime_r (scalar_t__*,struct tm*) ; 
 int p_snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * weekday_names ; 

int git__date_rfc2822_fmt(char *out, size_t len, const git_time *date)
{
	int written;
	struct tm gmt;
	time_t t;

	assert(out && date);

	t = (time_t) (date->time + date->offset * 60);

	if (p_gmtime_r (&t, &gmt) == NULL)
		return -1;

	written = p_snprintf(out, len, "%.3s, %u %.3s %.4u %02u:%02u:%02u %+03d%02d",
		weekday_names[gmt.tm_wday],
		gmt.tm_mday,
		month_names[gmt.tm_mon],
		gmt.tm_year + 1900,
		gmt.tm_hour, gmt.tm_min, gmt.tm_sec,
		date->offset / 60, date->offset % 60);

	if (written < 0 || (written > (int) len - 1))
		return -1;

	return 0;
}