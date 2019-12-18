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
struct sigaction {int /*<<< orphan*/  sa_mask; } ;
struct TYPE_4__ {int x_nlines; void* x_ncols; void* x_win; } ;
struct TYPE_3__ {int x_nlines; void* x_ncols; void* x_win; } ;

/* Variables and functions */
 void* COLS ; 
 int LINES ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  box (void*,char,char) ; 
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  crmode () ; 
 char* current_state ; 
 int curses_initialized ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 TYPE_2__ his_win ; 
 int /*<<< orphan*/  idlok (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * initscr () ; 
 void* line_win ; 
 TYPE_1__ my_win ; 
 void* newwin (int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  scrollok (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sig_sent ; 
 int /*<<< orphan*/  sig_winch ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclear (void*) ; 
 int /*<<< orphan*/  whline (void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  wrefresh (void*) ; 

void
init_display(void)
{
	struct sigaction sa;

	if (initscr() == NULL)
		errx(1, "Terminal type unset or lacking necessary features.");
	(void) sigaction(SIGTSTP, (struct sigaction *)0, &sa);
	sigaddset(&sa.sa_mask, SIGALRM);
	(void) sigaction(SIGTSTP, &sa, (struct sigaction *)0);
	curses_initialized = 1;
	clear();
	refresh();
	noecho();
	crmode();
	signal(SIGINT, sig_sent);
	signal(SIGPIPE, sig_sent);
	signal(SIGWINCH, sig_winch);
	/* curses takes care of ^Z */
	my_win.x_nlines = LINES / 2;
	my_win.x_ncols = COLS;
	my_win.x_win = newwin(my_win.x_nlines, my_win.x_ncols, 0, 0);
	idlok(my_win.x_win, TRUE);
	scrollok(my_win.x_win, TRUE);
	wclear(my_win.x_win);

	his_win.x_nlines = LINES / 2 - 1;
	his_win.x_ncols = COLS;
	his_win.x_win = newwin(his_win.x_nlines, his_win.x_ncols,
	    my_win.x_nlines+1, 0);
	idlok(my_win.x_win, TRUE);
	scrollok(his_win.x_win, TRUE);
	wclear(his_win.x_win);

	line_win = newwin(1, COLS, my_win.x_nlines, 0);
#if defined(hline) || defined(whline) || defined(NCURSES_VERSION)
	whline(line_win, 0, COLS);
#else
	box(line_win, '-', '-');
#endif
	wrefresh(line_win);
	/* let them know we are working on it */
	current_state = "No connection yet";
}