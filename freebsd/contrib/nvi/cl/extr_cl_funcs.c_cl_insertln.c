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

/* Variables and functions */
 int /*<<< orphan*/ * CLSP (int /*<<< orphan*/ *) ; 
 scalar_t__ ERR ; 
 int /*<<< orphan*/ * stdscr ; 
 scalar_t__ winsertln (int /*<<< orphan*/ *) ; 

int
cl_insertln(SCR *sp)
{
	WINDOW *win;
	win = CLSP(sp) ? CLSP(sp) : stdscr;
	/*
	 * The current line is expected to be blank after this operation,
	 * and the screen must support that semantic.
	 */
	return (winsertln(win) == ERR);
}