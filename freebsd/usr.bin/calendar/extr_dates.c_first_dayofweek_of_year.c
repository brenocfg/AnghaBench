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
struct cal_year {int year; int firstdayofweek; struct cal_year* nextyear; } ;

/* Variables and functions */
 struct cal_year* hyear ; 

int
first_dayofweek_of_year(int yy)
{
	struct cal_year *y;

	y = hyear;
	while (y != NULL) {
		if (y->year == yy)
			return (y->firstdayofweek);
		y = y->nextyear;
	}

	/* Should not happen */
	return (-1);
}