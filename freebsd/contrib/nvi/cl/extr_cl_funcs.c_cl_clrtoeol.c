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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {size_t coff; size_t cols; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/ * CLSP (TYPE_1__*) ; 
 scalar_t__ ERR ; 
 scalar_t__ IS_VSPLIT (TYPE_1__*) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * stdscr ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 scalar_t__ wclrtoeol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,size_t,size_t) ; 

int
cl_clrtoeol(SCR *sp)
{
	WINDOW *win;
#if 0
	size_t spcnt, y, x;
#endif

	win = CLSP(sp) ? CLSP(sp) : stdscr;

#if 0
	if (IS_VSPLIT(sp)) {
		/* The cursor must be returned to its original position. */
		getyx(win, y, x);
		for (spcnt = (sp->coff + sp->cols) - x; spcnt > 0; --spcnt)
			(void)waddch(win, ' ');
		(void)wmove(win, y, x);
		return (0);
	} else
#endif
		return (wclrtoeol(win) == ERR);
}