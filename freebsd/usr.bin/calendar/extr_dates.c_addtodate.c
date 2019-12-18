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
struct event {struct event* next; } ;
struct cal_day {struct event* events; } ;

/* Variables and functions */
 struct cal_day* find_day (int,int,int) ; 

void
addtodate(struct event *e, int year, int month, int day)
{
	struct cal_day *d;

	d = find_day(year, month, day);
	e->next = d->events;
	d->events = e;
}