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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; scalar_t__ tm_sec; } ;
typedef  int git_time_t ;

/* Variables and functions */

__attribute__((used)) static git_time_t tm_to_time_t(const struct tm *tm)
{
	static const int mdays[] = {
	    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	};
	int year = tm->tm_year - 70;
	int month = tm->tm_mon;
	int day = tm->tm_mday;

	if (year < 0 || year > 129) /* algo only works for 1970-2099 */
		return -1;
	if (month < 0 || month > 11) /* array bounds */
		return -1;
	if (month < 2 || (year + 2) % 4)
		day--;
	if (tm->tm_hour < 0 || tm->tm_min < 0 || tm->tm_sec < 0)
		return -1;
	return (year * 365 + (year + 1) / 4 + mdays[month] + day) * 24*60*60UL +
		tm->tm_hour * 60*60 + tm->tm_min * 60 + tm->tm_sec;
}