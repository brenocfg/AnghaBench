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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int /*<<< orphan*/  tm_sec; } ;

/* Variables and functions */
 void* ATOI2 (char*) ; 
 int LONG_MAX ; 
 int /*<<< orphan*/  badtime () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  isascii (char) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 struct tm* localtime (int*) ; 
 int mktime (struct tm*) ; 
 int offset ; 
 int shuttime ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strlen (char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  time (int*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static void
getoffset(char *timearg)
{
	struct tm *lt;
	char *p;
	time_t now;
	int maybe_today, this_year;
	char *timeunit;

	(void)time(&now);

	if (!strcasecmp(timearg, "now")) {		/* now */
		offset = 0;
		shuttime = now;
		return;
	}

	if (*timearg == '+') {				/* +minutes */
		if (!isdigit(*++timearg))
			badtime();
		errno = 0;
		offset = strtol(timearg, &timeunit, 10);
		if (offset < 0 || offset == LONG_MAX || errno != 0)
			badtime();
		if (timeunit[0] == '\0' || strcasecmp(timeunit, "m") == 0 ||
		    strcasecmp(timeunit, "min") == 0 ||
		    strcasecmp(timeunit, "mins") == 0) {
			offset *= 60;
		} else if (strcasecmp(timeunit, "h") == 0 ||
		    strcasecmp(timeunit, "hour") == 0 ||
		    strcasecmp(timeunit, "hours") == 0) {
			offset *= 60 * 60;
		} else if (strcasecmp(timeunit, "s") == 0 ||
		    strcasecmp(timeunit, "sec") == 0 ||
		    strcasecmp(timeunit, "secs") == 0) {
			offset *= 1;
		} else {
			badtime();
		}
		shuttime = now + offset;
		return;
	}

	/* handle hh:mm by getting rid of the colon */
	for (p = timearg; *p; ++p)
		if (!isascii(*p) || !isdigit(*p)) {
			if (*p == ':' && strlen(p) == 3) {
				p[0] = p[1];
				p[1] = p[2];
				p[2] = '\0';
			}
			else
				badtime();
		}

	unsetenv("TZ");					/* OUR timezone */
	lt = localtime(&now);				/* current time val */
	maybe_today = 1;

	switch(strlen(timearg)) {
	case 10:
		this_year = lt->tm_year;
		lt->tm_year = ATOI2(timearg);
		/*
		 * check if the specified year is in the next century.
		 * allow for one year of user error as many people will
		 * enter n - 1 at the start of year n.
		 */
		if (lt->tm_year < (this_year % 100) - 1)
			lt->tm_year += 100;
		/* adjust for the year 2000 and beyond */
		lt->tm_year += (this_year - (this_year % 100));
		/* FALLTHROUGH */
	case 8:
		lt->tm_mon = ATOI2(timearg);
		if (--lt->tm_mon < 0 || lt->tm_mon > 11)
			badtime();
		/* FALLTHROUGH */
	case 6:
		maybe_today = 0;
		lt->tm_mday = ATOI2(timearg);
		if (lt->tm_mday < 1 || lt->tm_mday > 31)
			badtime();
		/* FALLTHROUGH */
	case 4:
		lt->tm_hour = ATOI2(timearg);
		if (lt->tm_hour < 0 || lt->tm_hour > 23)
			badtime();
		lt->tm_min = ATOI2(timearg);
		if (lt->tm_min < 0 || lt->tm_min > 59)
			badtime();
		lt->tm_sec = 0;
		if ((shuttime = mktime(lt)) == -1)
			badtime();

		if ((offset = shuttime - now) < 0) {
			if (!maybe_today)
				errx(1, "that time is already past.");

			/*
			 * If the user only gave a time, assume that
			 * any time earlier than the current time
			 * was intended to be that time tomorrow.
			 */
			lt->tm_mday++;
			if ((shuttime = mktime(lt)) == -1)
				badtime();
			if ((offset = shuttime - now) < 0) {
				errx(1, "tomorrow is before today?");
			}
		}
		break;
	default:
		badtime();
	}
}