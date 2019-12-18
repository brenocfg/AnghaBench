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
typedef  int /*<<< orphan*/  tmp ;
typedef  long time_t ;
struct tm {int tm_mon; int tm_mday; int tm_year; } ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 struct tm* localtime (long*) ; 
 long mktime (struct tm*) ; 
 scalar_t__ numerics (char const*) ; 
 int /*<<< orphan*/  parse_datesub (char*,struct tm*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 long time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  weekday (char const**) ; 

time_t
parse_date(time_t dt, char const * str)
{
	char           *p;
	int             i;
	long            val;
	struct tm      *T;

	if (dt == 0)
		dt = time(NULL);

	while (*str && isspace((unsigned char)*str))
		++str;

	if (numerics(str)) {
		dt = strtol(str, &p, 0);
	} else if (*str == '+' || *str == '-') {
		val = strtol(str, &p, 0);
		switch (*p) {
		case 'h':
		case 'H':	/* hours */
			dt += (val * 3600L);
			break;
		case '\0':
		case 'm':
		case 'M':	/* minutes */
			dt += (val * 60L);
			break;
		case 's':
		case 'S':	/* seconds */
			dt += val;
			break;
		case 'd':
		case 'D':	/* days */
			dt += (val * 86400L);
			break;
		case 'w':
		case 'W':	/* weeks */
			dt += (val * 604800L);
			break;
		case 'o':
		case 'O':	/* months */
			T = localtime(&dt);
			T->tm_mon += (int) val;
			i = T->tm_mday;
			goto fixday;
		case 'y':
		case 'Y':	/* years */
			T = localtime(&dt);
			T->tm_year += (int) val;
			i = T->tm_mday;
	fixday:
			dt = mktime(T);
			T = localtime(&dt);
			if (T->tm_mday != i) {
				T->tm_mday = 1;
				dt = mktime(T);
				dt -= (time_t) 86400L;
			}
		default:	/* unknown */
			break;	/* leave untouched */
		}
	} else {
		char           *q, tmp[64];

		/*
		 * Skip past any weekday prefix
		 */
		weekday(&str);
		strlcpy(tmp, str, sizeof(tmp));
		str = tmp;
		T = localtime(&dt);

		/*
		 * See if we can break off any timezone
		 */
		while ((q = strrchr(tmp, ' ')) != NULL) {
			if (strchr("(+-", q[1]) != NULL)
				*q = '\0';
			else {
				int             j = 1;

				while (q[j] && isupper((unsigned char)q[j]))
					++j;
				if (q[j] == '\0')
					*q = '\0';
				else
					break;
			}
		}

		parse_datesub(tmp, T);
		dt = mktime(T);
	}
	return dt;
}