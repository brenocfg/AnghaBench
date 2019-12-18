#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int y; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 TYPE_1__ jiswitch ; 
 int ndaysji (TYPE_1__*) ; 
 int nswitch ; 

__attribute__((used)) static int
ndaysgi(date *idt)
{
	int     nd;		/* Number of days--return value */

	/* Cache nswitch if not already done */
	if (nswitch == 0)
		nswitch = ndaysji(&jiswitch);

	/*
	 * Assume Julian calendar and adapt to Gregorian if necessary, i. e.
	 * younger than nswitch. Gregori deleted
	 * the ten days from Oct 5th to Oct 14th 1582.
	 * Thereafter years which are multiples of 100 and not multiples
	 * of 400 were not leap years anymore.
	 * This makes the average length of a year
	 * 365d +.25d - .01d + .0025d = 365.2425d. But the tropical
	 * year measures 365.2422d. So in 10000/3 years we are
	 * again one day ahead of the earth. Sigh :-)
	 * (d is the average length of a day and tropical year is the
	 * time from one spring point to the next.)
	 */
	if ((nd = ndaysji(idt)) == -1)
		return (-1);
	if (idt->y >= 1600)
		nd = (nd - 10 - (idt->y - 1600) / 100 + (idt->y - 1600) / 400);
	else if (nd > nswitch)
		nd -= 10;
	return (nd);
}