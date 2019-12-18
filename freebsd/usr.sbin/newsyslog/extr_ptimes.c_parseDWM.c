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
struct tm {long tm_hour; long tm_wday; int tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct ptime_data {struct tm tm; int /*<<< orphan*/  tmspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSPEC_DAYOFMONTH ; 
 int /*<<< orphan*/  TSPEC_DAYOFWEEK ; 
 int /*<<< orphan*/  TSPEC_HOUROFDAY ; 
 int /*<<< orphan*/  TSPEC_LDAYOFMONTH ; 
 int days_pmonth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char const) ; 
 long strtol (char const*,char**,int) ; 
 char tolower (char const) ; 

__attribute__((used)) static int
parseDWM(struct ptime_data *ptime, const char *s)
{
	int daysmon, Dseen, WMseen;
	const char *endval;
	char *tmp;
	long l;
	struct tm tm;

	/* Save away the number of days in this month */
	tm = ptime->tm;
	daysmon = days_pmonth(tm.tm_mon, tm.tm_year);

	WMseen = Dseen = 0;
	ptime->tmspec = TSPEC_HOUROFDAY;
	for (;;) {
		endval = NULL;
		switch (*s) {
		case 'D':
			if (Dseen)
				return (-1);
			Dseen++;
			ptime->tmspec |= TSPEC_HOUROFDAY;
			s++;
			l = strtol(s, &tmp, 10);
			if (l < 0 || l > 23)
				return (-1);
			endval = tmp;
			tm.tm_hour = l;
			break;

		case 'W':
			if (WMseen)
				return (-1);
			WMseen++;
			ptime->tmspec |= TSPEC_DAYOFWEEK;
			s++;
			l = strtol(s, &tmp, 10);
			if (l < 0 || l > 6)
				return (-1);
			endval = tmp;
			if (l != tm.tm_wday) {
				int save;

				if (l < tm.tm_wday) {
					save = 6 - tm.tm_wday;
					save += (l + 1);
				} else {
					save = l - tm.tm_wday;
				}

				tm.tm_mday += save;

				if (tm.tm_mday > daysmon) {
					tm.tm_mon++;
					tm.tm_mday = tm.tm_mday - daysmon;
				}
			}
			break;

		case 'M':
			if (WMseen)
				return (-1);
			WMseen++;
			ptime->tmspec |= TSPEC_DAYOFMONTH;
			s++;
			if (tolower(*s) == 'l') {
				/* User wants the last day of the month. */
				ptime->tmspec |= TSPEC_LDAYOFMONTH;
				tm.tm_mday = daysmon;
				endval = s + 1;
			} else {
				l = strtol(s, &tmp, 10);
				if (l < 1 || l > 31)
					return (-1);

				if (l > daysmon)
					return (-1);
				endval = tmp;
				tm.tm_mday = l;
			}
			break;

		default:
			return (-1);
			break;
		}

		if (endval == NULL)
			return (-1);
		else if (*endval == '\0' || isspace(*endval))
			break;
		else
			s = endval;
	}

	ptime->tm = tm;
	return (0);
}