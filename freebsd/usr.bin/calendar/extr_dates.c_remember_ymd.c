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
struct cal_month {int month; struct cal_day* days; struct cal_month* nextmonth; } ;
struct cal_day {int dayofmonth; struct cal_day* nextday; } ;

/* Variables and functions */
 scalar_t__ debug_remember ; 
 struct cal_year* hyear ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

int
remember_ymd(int yy, int mm, int dd)
{
	struct cal_year *y;
	struct cal_month *m;
	struct cal_day *d;

	if (debug_remember)
		printf("remember_ymd: %d - %d - %d\n", yy, mm, dd);

	y = hyear;
	while (y != NULL) {
		if (y->year != yy) {
			y = y->nextyear;
			continue;
		}
		m = y->months;
		while (m != NULL) {
			if (m->month != mm) {
				m = m->nextmonth;
				continue;
			}
			d = m->days;
			while (d != NULL) {
				if (d->dayofmonth == dd)
					return (1);
				d = d->nextday;
				continue;
			}
			return (0);
		}
		return (0);
	}
	return (0);
}