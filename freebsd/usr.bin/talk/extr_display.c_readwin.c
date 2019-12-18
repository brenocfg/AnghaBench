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

/* Variables and functions */
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int winch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

int
readwin(WINDOW *win, int line, int col)
{
	int oldline, oldcol;
	int c;

	getyx(win, oldline, oldcol);
	wmove(win, line, col);
	c = winch(win);
	wmove(win, oldline, oldcol);
	return (c);
}