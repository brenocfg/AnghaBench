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
typedef  scalar_t__ time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_isdst; scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; } ;

/* Variables and functions */
 scalar_t__ UINT32_MAX ; 
 int atoi (char*) ; 
 scalar_t__ isdigit (char) ; 
 struct tm* localtime (scalar_t__*) ; 
 scalar_t__ mktime (struct tm*) ; 
 char const** months ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

int
atot(char *p, time_t *store)
{
	static struct tm *lt;
	char *t;
	const char **mp;
	time_t tval;
	int day, month, year;

	if (!*p) {
		*store = 0;
		return (0);
	}
	if (!lt) {
		unsetenv("TZ");
		(void)time(&tval);
		lt = localtime(&tval);
	}
	if (!(t = strtok(p, " \t")))
		goto bad;
	if (isdigit(*t)) {
		month = atoi(t);
	} else {
		for (mp = months;; ++mp) {
			if (!*mp)
				goto bad;
			if (!strncasecmp(*mp, t, 3)) {
				month = mp - months + 1;
				break;
			}
		}
	}
	if (!(t = strtok(NULL, " \t,")) || !isdigit(*t))
		goto bad;
	day = atoi(t);
	if (!(t = strtok(NULL, " \t,")) || !isdigit(*t))
		goto bad;
	year = atoi(t);
	if (day < 1 || day > 31 || month < 1 || month > 12)
		goto bad;
	/* Allow two digit years 1969-2068 */
	if (year < 69)
		year += 2000;
	else if (year < 100)
		year += 1900;
	if (year < 1969)
bad:		return (1);
	lt->tm_year = year - 1900;
	lt->tm_mon = month - 1;
	lt->tm_mday = day;
	lt->tm_hour = 0;
	lt->tm_min = 0;
	lt->tm_sec = 0;
	lt->tm_isdst = -1;
	if ((tval = mktime(lt)) < 0)
		return (1);
#ifndef __i386__
	/*
	 * PR227589: The pwd.db and spwd.db files store the change and expire
	 * dates as unsigned 32-bit ints which overflow in 2106, so larger
	 * values must be rejected until the introduction of a v5 password
	 * database.  i386 has 32-bit time_t and so dates beyond y2038 are
	 * already rejected by mktime above.
	 */
	if (tval > UINT32_MAX)
		return (1);
#endif
	*store = tval;
	return (0);
}