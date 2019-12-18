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
typedef  int /*<<< orphan*/  tm ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LC_ALL_MASK ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freelocale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newlocale (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* strptime_l (char const*,char const*,struct tm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_datesub(char const * str, struct tm *t)
{
	struct tm	 tm;
	locale_t	 l;
	int		 i;
	char		*ret;
	const char	*valid_formats[] = {
		"%d-%b-%y",
		"%d-%b-%Y",
		"%d-%m-%y",
		"%d-%m-%Y",
		"%H:%M %d-%b-%y",
		"%H:%M %d-%b-%Y",
		"%H:%M %d-%m-%y",
		"%H:%M %d-%m-%Y",
		"%H:%M:%S %d-%b-%y",
		"%H:%M:%S %d-%b-%Y",
		"%H:%M:%S %d-%m-%y",
		"%H:%M:%S %d-%m-%Y",
		"%d-%b-%y %H:%M",
		"%d-%b-%Y %H:%M",
		"%d-%m-%y %H:%M",
		"%d-%m-%Y %H:%M",
		"%d-%b-%y %H:%M:%S",
		"%d-%b-%Y %H:%M:%S",
		"%d-%m-%y %H:%M:%S",
		"%d-%m-%Y %H:%M:%S",
		"%H:%M\t%d-%b-%y",
		"%H:%M\t%d-%b-%Y",
		"%H:%M\t%d-%m-%y",
		"%H:%M\t%d-%m-%Y",
		"%H:%M\t%S %d-%b-%y",
		"%H:%M\t%S %d-%b-%Y",
		"%H:%M\t%S %d-%m-%y",
		"%H:%M\t%S %d-%m-%Y",
		"%d-%b-%y\t%H:%M",
		"%d-%b-%Y\t%H:%M",
		"%d-%m-%y\t%H:%M",
		"%d-%m-%Y\t%H:%M",
		"%d-%b-%y\t%H:%M:%S",
		"%d-%b-%Y\t%H:%M:%S",
		"%d-%m-%y\t%H:%M:%S",
		"%d-%m-%Y\t%H:%M:%S",
		NULL,
	};

	l = newlocale(LC_ALL_MASK, "C", NULL);

	memset(&tm, 0, sizeof(tm));
	for (i=0; valid_formats[i] != NULL; i++) {
		ret = strptime_l(str, valid_formats[i], &tm, l);
		if (ret && *ret == '\0') {
			t->tm_mday = tm.tm_mday;
			t->tm_mon = tm.tm_mon;
			t->tm_year = tm.tm_year;
			t->tm_hour = tm.tm_hour;
			t->tm_min = tm.tm_min;
			t->tm_sec = tm.tm_sec;
			freelocale(l);
			return;
		}
	}

	freelocale(l);

	errx(EXIT_FAILURE, "Invalid date");
}