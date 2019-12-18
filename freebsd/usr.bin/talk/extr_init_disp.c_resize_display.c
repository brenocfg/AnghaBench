#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct winsize {int ws_row; scalar_t__ ws_col; } ;
struct TYPE_4__ {int x_nlines; scalar_t__ x_ncols; int /*<<< orphan*/  x_win; } ;
struct TYPE_3__ {int x_nlines; scalar_t__ x_ncols; int /*<<< orphan*/  x_win; } ;

/* Variables and functions */
 scalar_t__ COLS ; 
 int LINES ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  box (int /*<<< orphan*/ ,char,char) ; 
 int /*<<< orphan*/  clearok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ his_win ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  line_win ; 
 int /*<<< orphan*/  mvwin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ my_win ; 
 int /*<<< orphan*/  resizeterm (int,scalar_t__) ; 
 int /*<<< orphan*/  whline (int /*<<< orphan*/ ,char,scalar_t__) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wresize (int /*<<< orphan*/ ,int,scalar_t__) ; 

void
resize_display(void)
{
	struct winsize ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) < 0 ||
	    (ws.ws_row == LINES && ws.ws_col == COLS))
		return;

	/* Update curses' internal state with new window size. */
	resizeterm(ws.ws_row, ws.ws_col);

	/*
	 * Resize each window but wait to refresh the screen until
	 * everything has been drawn so the cursor is in the right spot.
	 */
	my_win.x_nlines = LINES / 2;
	my_win.x_ncols = COLS;
	wresize(my_win.x_win, my_win.x_nlines, my_win.x_ncols);
	mvwin(my_win.x_win, 0, 0);
	clearok(my_win.x_win, TRUE);

	his_win.x_nlines = LINES / 2 - 1;
	his_win.x_ncols = COLS;
	wresize(his_win.x_win, his_win.x_nlines, his_win.x_ncols);
	mvwin(his_win.x_win, my_win.x_nlines + 1, 0);
	clearok(his_win.x_win, TRUE);

	wresize(line_win, 1, COLS);
	mvwin(line_win, my_win.x_nlines, 0);
#if defined(NCURSES_VERSION) || defined(whline)
	whline(line_win, '-', COLS);
#else
	wmove(line_win, my_win.x_nlines, 0);
	box(line_win, '-', '-');
#endif

	/* Now redraw the screen. */
	wrefresh(his_win.x_win);
	wrefresh(line_win);
	wrefresh(my_win.x_win);
}