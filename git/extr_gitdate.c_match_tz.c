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

/* Variables and functions */
 int strtoul (char const*,char**,int) ; 

__attribute__((used)) static int match_tz(const char *date, int *offp)
{
	char *end;
	int hour = strtoul(date + 1, &end, 10);
	int n = end - (date + 1);
	int min = 0;

	if (n == 4) {
		/* hhmm */
		min = hour % 100;
		hour = hour / 100;
	} else if (n != 2) {
		min = 99; /* random crap */
	} else if (*end == ':') {
		/* hh:mm? */
		min = strtoul(end + 1, &end, 10);
		if (end - (date + 1) != 5)
			min = 99; /* random crap */
	} /* otherwise we parsed "hh" */

	/*
	 * Don't accept any random crap. Even though some places have
	 * offset larger than 12 hours (e.g. Pacific/Kiritimati is at
	 * UTC+14), there is something wrong if hour part is much
	 * larger than that. We might also want to check that the
	 * minutes are divisible by 15 or something too. (Offset of
	 * Kathmandu, Nepal is UTC+5:45)
	 */
	if (min < 60 && hour < 24) {
		int offset = hour * 60 + min;
		if (*date == '-')
			offset = -offset;
		*offp = offset;
	}
	return end - date;
}