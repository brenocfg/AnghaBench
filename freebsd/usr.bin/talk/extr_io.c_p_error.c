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
struct TYPE_2__ {int /*<<< orphan*/  x_win; } ;

/* Variables and functions */
 scalar_t__ LINES ; 
 int /*<<< orphan*/  current_line ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  move (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ my_win ; 
 int /*<<< orphan*/  quit () ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void
p_error(const char *string)
{
	wmove(my_win.x_win, current_line, 0);
	wprintw(my_win.x_win, "[%s : %s (%d)]\n",
	    string, strerror(errno), errno);
	wrefresh(my_win.x_win);
	move(LINES-1, 0);
	refresh();
	quit();
}