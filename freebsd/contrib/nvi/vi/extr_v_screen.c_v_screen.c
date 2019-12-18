#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_11__ {struct TYPE_11__* nextdisp; TYPE_1__* gp; } ;
struct TYPE_10__ {int /*<<< orphan*/  dq; } ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  SC_COMEDIT ; 
 int SC_SSWITCH ; 
 int SC_STATUS ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  q ; 

int
v_screen(SCR *sp, VICMD *vp)
{
	/*
	 * You can't leave a colon command-line edit window -- it's not that
	 * it won't work, but it gets real weird, real fast when you execute
	 * a colon command out of a window that was forked from a window that's
	 * now backgrounded...  You get the idea.
	 */
	if (F_ISSET(sp, SC_COMEDIT)) {
		msgq(sp, M_ERR,
		    "308|Enter <CR> to execute a command, :q to exit");
		return (1);
	}
		
	/*
	 * Try for the next lower screen, or, go back to the first
	 * screen on the stack.
	 */
	if (TAILQ_NEXT(sp, q) != NULL)
		sp->nextdisp = TAILQ_NEXT(sp, q);
	else if (TAILQ_FIRST(sp->gp->dq) == sp) {
		msgq(sp, M_ERR, "187|No other screen to switch to");
		return (1);
	} else
		sp->nextdisp = TAILQ_FIRST(sp->gp->dq);

	F_SET(sp->nextdisp, SC_STATUS);
	F_SET(sp, SC_SSWITCH | SC_STATUS);
	return (0);
}