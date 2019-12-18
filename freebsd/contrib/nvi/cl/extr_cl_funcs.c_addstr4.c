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
typedef  int /*<<< orphan*/  WINDOW ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CL_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/ * CLP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CLSP (int /*<<< orphan*/ *) ; 
 scalar_t__ ERR ; 
 int /*<<< orphan*/  F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SPLIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LASTLINE (int /*<<< orphan*/ *) ; 
 size_t RLNO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * stdscr ; 
 scalar_t__ waddnstr (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ waddnwstr (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  wstandend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wstandout (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
addstr4(SCR *sp, void *str, size_t len, int wide)
{
	CL_PRIVATE *clp;
	WINDOW *win;
	size_t y, x;
	int iv;

	clp = CLP(sp);
	win = CLSP(sp) ? CLSP(sp) : stdscr;

	/*
	 * If ex isn't in control, it's the last line of the screen and
	 * it's a split screen, use inverse video.
	 */
	iv = 0;
	getyx(win, y, x);
	if (!F_ISSET(sp, SC_SCR_EXWROTE) &&
	    y == RLNO(sp, LASTLINE(sp)) && IS_SPLIT(sp)) {
		iv = 1;
		(void)wstandout(win);
	}

#ifdef USE_WIDECHAR
	if (wide) {
	    if (waddnwstr(win, str, len) == ERR)
		return (1);
	} else 
#endif
	    if (waddnstr(win, str, len) == ERR)
		    return (1);

	if (iv)
		(void)wstandend(win);
	return (0);
}