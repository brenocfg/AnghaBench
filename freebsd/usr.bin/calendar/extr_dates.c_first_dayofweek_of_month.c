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
struct cal_year {int year; struct cal_month* months; struct cal_year* nextyear; } ;
struct cal_month {int month; int firstdayofweek; struct cal_month* nextmonth; } ;

/* Variables and functions */
 struct cal_year* hyear ; 

int
first_dayofweek_of_month(int yy, int mm)
{
	struct cal_year *y;
	struct cal_month *m;

	y = hyear;
	while (y != NULL) {
		if (y->year != yy) {
			y = y->nextyear;
			continue;
		}
		m = y->months;
		while (m != NULL) {
			if (m->month == mm)
				return (m->firstdayofweek);
			m = m->nextmonth;
		}
		/* No data for this month */
		return (-1);
	}

	/* No data for this year.  Error? */
        return (-1);
}