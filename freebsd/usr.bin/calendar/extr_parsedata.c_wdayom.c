#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* monthdays; } ;

/* Variables and functions */
 int first_dayofweek_of_month (int,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 TYPE_1__* yearinfo ; 

__attribute__((used)) static int
wdayom (int day, int offset, int month, int year)
{
/* Weekday of first day in month */
	int wday1;                                /* first day of month */
/* Weekday of last day in month */
	int wdayn;
	int d;

	wday1 = first_dayofweek_of_month(year, month);
	if (wday1 < 0)                          /* not set */
		return (wday1);
	/*
	 * Date of zeroth or first of our weekday in month, depending on the
	 * relationship with the first of the month.  The range is -6:6.
	 */
	d = (day - wday1 + 1) % 7;
	/*
	 * Which way are we counting?  Offset 0 is invalid, abs (offset) > 5 is
	 * meaningless, but that's OK.  Offset 5 may or may not be meaningless,
	 * so there's no point in complaining for complaining's sake.
	 */
	if (offset < 0) {			/* back from end of month */
						/* FIXME */
		wdayn = d;
		while (wdayn <= yearinfo->monthdays[month])
			wdayn += 7;
		d = offset * 7 + wdayn;
	} else if (offset > 0){
		if (d > 0)
			d += offset * 7 - 7;
		else
			d += offset * 7;
	} else
		warnx ("Invalid offset 0");
	return (d);
}