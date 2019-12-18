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
struct event {int dummy; } ;
struct cal_year {struct cal_month* months; struct cal_year* nextyear; } ;
struct cal_month {struct cal_day* days; struct cal_month* nextmonth; } ;
struct cal_day {struct event* events; struct cal_day* nextday; } ;

/* Variables and functions */
 struct cal_year* hyear ; 

int
walkthrough_dates(struct event **e)
{
	static struct cal_year *y = NULL;
	static struct cal_month *m = NULL;
	static struct cal_day *d = NULL;

	if (y == NULL) {
		y = hyear;
		m = y->months;
		d = m->days;
		*e = d->events;
		return (1);
	}
	if (d->nextday != NULL) {
		d = d->nextday;
		*e = d->events;
		return (1);
	}
	if (m->nextmonth != NULL) {
		m = m->nextmonth;
		d = m->days;
		*e = d->events;
		return (1);
	}
	if (y->nextyear != NULL) {
		y = y->nextyear;
		m = y->months;
		d = m->days;
		*e = d->events;
		return (1);
	}

	return (0);
}