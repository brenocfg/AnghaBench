#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int y; int m; int d; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 TYPE_1__* idt2date (TYPE_1__*,TYPE_1__*) ; 
 int* month1 ; 
 int ndaysji (TYPE_1__*) ; 

date *
jdate(int ndays, date *dt)
{
	date    idt;		/* Internal date representation */
	int     r;		/* hold the rest of days */

	/*
	 * Compute the year by starting with an approximation not smaller
	 * than the answer and using linear search for the greatest
	 * year which does not begin after ndays.
	 */
	idt.y = ndays / 365;
	idt.m = 0;
	idt.d = 0;
	while ((r = ndaysji(&idt)) > ndays)
		idt.y--;
	
	/*
	 * Set r to the days left in the year and compute the month by
	 * linear search as the largest month that does not begin after r
	 * days.
	 */
	r = ndays - r;
	for (idt.m = 11; month1[idt.m] > r; idt.m--)
		;

	/* Compute the days left in the month */
	idt.d = r - month1[idt.m];

	/* return external representation of the date */
	return (idt2date(dt, &idt));
}