#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* scr_move ) (TYPE_1__*,size_t,size_t) ;int /*<<< orphan*/  (* scr_insertln ) (TYPE_1__*) ;int /*<<< orphan*/  (* scr_deleteln ) (TYPE_1__*) ;int /*<<< orphan*/  (* scr_cursor ) (TYPE_1__*,size_t*,size_t*) ;int /*<<< orphan*/  (* scr_clrtoeol ) (TYPE_1__*) ;} ;
struct TYPE_14__ {TYPE_2__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ GS ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ONELINE (TYPE_1__*) ; 
 scalar_t__ IS_VSPLIT (TYPE_1__*) ; 
 size_t LASTLINE (TYPE_1__*) ; 
 int /*<<< orphan*/  SC_SCR_REDRAW ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,size_t*,size_t*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,size_t,size_t) ; 

__attribute__((used)) static int
vs_deleteln(SCR *sp, int cnt)
{
	GS *gp;
	size_t oldy, oldx;

	gp = sp->gp;

	/* If the screen is vertically split, we can't scroll it. */
	if (IS_VSPLIT(sp)) {
		F_SET(sp, SC_SCR_REDRAW);
		return (0);
	}
		
	if (IS_ONELINE(sp))
		(void)gp->scr_clrtoeol(sp);
	else {
		(void)gp->scr_cursor(sp, &oldy, &oldx);
		while (cnt--) {
			(void)gp->scr_deleteln(sp);
			(void)gp->scr_move(sp, LASTLINE(sp), 0);
			(void)gp->scr_insertln(sp);
			(void)gp->scr_move(sp, oldy, oldx);
		}
	}
	return (0);
}