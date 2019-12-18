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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_7__ {int /*<<< orphan*/  coff; int /*<<< orphan*/  roff; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/ * CLSP (TYPE_1__*) ; 
 scalar_t__ ERR ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  RCNO (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  RLNO (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdscr ; 
 scalar_t__ wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cl_move(SCR *sp, size_t lno, size_t cno)
{
	WINDOW *win;
	win = CLSP(sp) ? CLSP(sp) : stdscr;
	/* See the comment in cl_cursor. */
	if (wmove(win, RLNO(sp, lno), RCNO(sp, cno)) == ERR) {
		msgq(sp, M_ERR, "Error: move: l(%zu + %zu) c(%zu + %zu)",
		    lno, sp->roff, cno, sp->coff);
		return (1);
	}
	return (0);
}