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
struct tm {int tm_year; long tm_mon; long tm_mday; } ;

/* Variables and functions */
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
assign_date(struct tm *tm, long mday, long mon, long year)
{

   /*
    * Convert year into tm_year format (year - 1900).
    * We may be given the year in 2 digit, 4 digit, or tm_year format.
    */
    if (year != -1) {
	if (year >= 1900)
		year -= 1900;   /* convert from 4 digit year */
	else if (year < 100) {
		/* convert from 2 digit year */
		struct tm *lt;
		time_t now;

		time(&now);
		lt = localtime(&now);

		/* Convert to tm_year assuming current century */
		year += (lt->tm_year / 100) * 100;

		if (year == lt->tm_year - 1) year++;
		else if (year < lt->tm_year)
			year += 100;    /* must be in next century */
	}
    }

    if (year < 0 &&
	(tm->tm_mon > mon ||(tm->tm_mon == mon && tm->tm_mday > mday)))
	year = tm->tm_year + 1;

    tm->tm_mday = mday;
    tm->tm_mon = mon;

    if (year >= 0)
	tm->tm_year = year;
}