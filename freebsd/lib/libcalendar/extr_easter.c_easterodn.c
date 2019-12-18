#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int d; int m; int y; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 int ndaysj (TYPE_1__*) ; 
 size_t weekday (int) ; 

__attribute__((used)) static int
easterodn(int y)
{
	/*
	 * Table for the easter limits in one metonic (19-year) cycle. 21
	 * to 31 is in March, 1 through 18 in April. Easter is the first
	 * sunday after the easter limit.
	 */
	int     mc[] = {5, 25, 13, 2, 22, 10, 30, 18, 7, 27, 15, 4,
		    24, 12, 1, 21, 9, 29, 17};

	/* Offset from a weekday to next sunday */
	int     ns[] = {6, 5, 4, 3, 2, 1, 7};
	date	dt;
	int     dn;

	/* Assign the easter limit of y to dt */
	dt.d = mc[y % 19];

	if (dt.d < 21)
		dt.m = 4;
	else
		dt.m = 3;

	dt.y = y;

	/* Return the next sunday after the easter limit */
	dn = ndaysj(&dt);
	return (dn + ns[weekday(dn)]);
}