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
struct cal_year {int year; int firstdayofweek; struct cal_year* nextyear; struct cal_month* months; } ;
struct cal_month {int month; int firstdayjulian; int firstdayofweek; struct cal_month* nextmonth; struct cal_day* days; } ;
struct cal_day {int dayofmonth; int julianday; int dayofweek; struct cal_day* nextday; } ;

/* Variables and functions */
 struct cal_year* hyear ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

void
dumpdates(void)
{
	struct cal_year *y;
	struct cal_month *m;
	struct cal_day *d;

	y = hyear;
	while (y != NULL) {
		printf("%-5d (wday:%d)\n", y->year, y->firstdayofweek);
		m = y->months;
		while (m != NULL) {
			printf("-- %-5d (julian:%d, dow:%d)\n", m->month,
			    m->firstdayjulian, m->firstdayofweek);
			d = m->days;
			while (d != NULL) {
				printf("  -- %-5d (julian:%d, dow:%d)\n",
				    d->dayofmonth, d->julianday, d->dayofweek);
				d = d->nextday;
			}
			m = m->nextmonth;
		}
		y = y->nextyear;
	}
}