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
struct TYPE_3__ {int y; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 int firstweek (int) ; 
 int /*<<< orphan*/  gdate (int,TYPE_1__*) ; 

int
week(int nd, int *y)
{
	date    dt;
	int     fw;		/* 1st day of week 1 of previous, this and
				 * next year */
	gdate(nd, &dt);
	for (*y = dt.y + 1; nd < (fw = firstweek(*y)); (*y)--)
		;
	return ((nd - fw) / 7 + 1);
}