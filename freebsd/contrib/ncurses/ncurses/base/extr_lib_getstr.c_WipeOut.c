#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chtype ;
struct TYPE_7__ {int _cury; int _curx; } ;
typedef  TYPE_1__ WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  getyx (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  waddch (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waddstr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  wmove (TYPE_1__*,int,int) ; 

__attribute__((used)) static char *
WipeOut(WINDOW *win, int y, int x, char *first, char *last, int echoed)
{
    if (last > first) {
	*--last = '\0';
	if (echoed) {
	    int y1 = win->_cury;
	    int x1 = win->_curx;

	    wmove(win, y, x);
	    waddstr(win, first);
	    getyx(win, y, x);
	    while (win->_cury < y1
		   || (win->_cury == y1 && win->_curx < x1))
		waddch(win, (chtype) ' ');

	    wmove(win, y, x);
	}
    }
    return last;
}