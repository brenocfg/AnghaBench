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

/* Variables and functions */
 int /*<<< orphan*/  INSET ; 
 int barlabels (int) ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ numbers ; 
 int numlabels (int) ; 
 int /*<<< orphan*/  wclrtobot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

void
labeliostat(void)
{
	int row;

	row = 0;
	wmove(wnd, row, 0); wclrtobot(wnd);
	mvwaddstr(wnd, row++, INSET,
	    "/0%  /10  /20  /30  /40  /50  /60  /70  /80  /90  /100");
	mvwaddstr(wnd, row++, 0, "cpu  user|");
	mvwaddstr(wnd, row++, 0, "     nice|");
	mvwaddstr(wnd, row++, 0, "   system|");
	mvwaddstr(wnd, row++, 0, "interrupt|");
	mvwaddstr(wnd, row++, 0, "     idle|");
	if (numbers)
		row = numlabels(row + 1);
	else
		row = barlabels(row + 1);
}