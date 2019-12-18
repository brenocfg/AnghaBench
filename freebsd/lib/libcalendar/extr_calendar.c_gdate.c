#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int y; int m; int d; } ;
typedef  TYPE_1__ date ;
struct TYPE_10__ {int y; size_t m; int d; } ;

/* Variables and functions */
 TYPE_1__* idt2date (TYPE_1__*,TYPE_1__*) ; 
 TYPE_3__ jiswitch ; 
 int* month1 ; 
 int* month1s ; 
 int ndaysgi (TYPE_1__*) ; 

date   *
gdate(int ndays, date *dt)
{
	int const *montht;	/* month-table */
	date    idt;		/* for internal date representation */
	int     r;		/* holds the rest of days */

	/*
	 * Compute the year by starting with an approximation not smaller
	 * than the answer and search linearly for the greatest year not
	 * starting after ndays.
	 */
	idt.y = ndays / 365;
	idt.m = 0;
	idt.d = 0;
	while ((r = ndaysgi(&idt)) > ndays)
		idt.y--;

	/*
	 * Set ndays to the number of days left and compute by linear
	 * search the greatest month which does not start after ndays. We
	 * use the table month1 which provides for each month the number
	 * of days that elapsed in the year before that month. Here the
	 * year 1582 is special, as 10 days are left out in October to
	 * resynchronize the calendar with the earth's orbit. October 4th
	 * 1582 is followed by October 15th 1582. We use the "switch"
	 * table month1s for this year.
	 */
	ndays = ndays - r;
	if (idt.y == 1582)
		montht = month1s;
	else
		montht = month1;

	for (idt.m = 11; montht[idt.m] > ndays; idt.m--)
		;

	idt.d = ndays - montht[idt.m]; /* the rest is the day in month */

	/* Advance ten days deleted from October if after switch in Oct 1582 */
	if (idt.y == jiswitch.y && idt.m == jiswitch.m && jiswitch.d < idt.d)
		idt.d += 10;

	/* return external representation of found date */
	return (idt2date(dt, &idt));
}