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
typedef  int time_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int snprintf (char*,int,char*,int) ; 

const char *
sec2str(const struct timespec *total)
{
	static char result[256];
	int days, hours, mins, secs;
	int first = 1;
	char *p = result;
	char *ep = &result[sizeof(result)];
	int n;
	struct timespec now;
	time_t tsec;

	clock_gettime(CLOCK_MONOTONIC_FAST, &now);
	tsec  = total->tv_sec;
	tsec += total->tv_nsec / 1000 / 1000000;
	tsec -= now.tv_sec;
	tsec -= now.tv_nsec / 1000 / 1000000;

	days = tsec / 3600 / 24;
	hours = (tsec / 3600) % 24;
	mins = (tsec / 60) % 60;
	secs = tsec % 60;

	if (days) {
		first = 0;
		n = snprintf(p, ep - p, "%dd", days);
		if (n < 0 || n >= ep - p)
			return "?";
		p += n;
	}
	if (!first || hours) {
		first = 0;
		n = snprintf(p, ep - p, "%dh", hours);
		if (n < 0 || n >= ep - p)
			return "?";
		p += n;
	}
	if (!first || mins) {
		first = 0;
		n = snprintf(p, ep - p, "%dm", mins);
		if (n < 0 || n >= ep - p)
			return "?";
		p += n;
	}
	snprintf(p, ep - p, "%ds", secs);

	return (result);
}