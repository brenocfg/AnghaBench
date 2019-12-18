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
struct TYPE_3__ {int y; int m; scalar_t__ d; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 int ndaysgi (TYPE_1__*) ; 
 int weekday (int) ; 

__attribute__((used)) static int
firstweek(int y)
{
	date idt;
	int nd, wd;

	idt.y = y - 1;   /* internal representation of y-1-1 */
	idt.m = 10;
	idt.d = 0;

	nd = ndaysgi(&idt);
	/*
	 * If more than 3 days of this week are in the preceding year, the
	 * next week is week 1 (and the next monday is the answer),
	 * otherwise this week is week 1 and the last monday is the
	 * answer.
	 */
	if ((wd = weekday(nd)) > 3)
		return (nd - wd + 7);
	else
		return (nd - wd);
}