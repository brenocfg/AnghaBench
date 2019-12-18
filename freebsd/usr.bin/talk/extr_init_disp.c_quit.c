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
struct TYPE_2__ {int /*<<< orphan*/  x_win; scalar_t__ x_nlines; } ;

/* Variables and functions */
 scalar_t__ curses_initialized ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_1__ his_win ; 
 scalar_t__ invitation_waiting ; 
 int /*<<< orphan*/  send_delete () ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void
quit(void)
{

	if (curses_initialized) {
		wmove(his_win.x_win, his_win.x_nlines-1, 0);
		wclrtoeol(his_win.x_win);
		wrefresh(his_win.x_win);
		endwin();
	}
	if (invitation_waiting)
		send_delete();
	exit(0);
}