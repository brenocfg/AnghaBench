#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cchar_t ;
struct TYPE_4__ {int _curx; int _cury; } ;
typedef  TYPE_1__ WINDOW ;
typedef  void* NCURSES_SIZE_T ;

/* Variables and functions */
 scalar_t__ ERR ; 
 int /*<<< orphan*/  blankchar ; 
 scalar_t__ wadd_wch_literal (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fill_cells(WINDOW *win, int count)
{
    cchar_t blank = blankchar;
    int save_x = win->_curx;
    int save_y = win->_cury;

    while (count-- > 0) {
	if (wadd_wch_literal(win, blank) == ERR)
	    break;
    }
    win->_curx = (NCURSES_SIZE_T) save_x;
    win->_cury = (NCURSES_SIZE_T) save_y;
}