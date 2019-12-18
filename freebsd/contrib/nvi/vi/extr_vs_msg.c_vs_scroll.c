#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sw_t ;
struct TYPE_15__ {scalar_t__ totalcount; scalar_t__ linecount; } ;
typedef  TYPE_1__ VI_PRIVATE ;
struct TYPE_17__ {int /*<<< orphan*/  (* scr_insertln ) (TYPE_2__*) ;int /*<<< orphan*/  (* scr_move ) (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* scr_deleteln ) (TYPE_2__*) ;} ;
struct TYPE_16__ {scalar_t__ rows; scalar_t__ t_maxrows; TYPE_3__* gp; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ GS ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ONELINE (TYPE_2__*) ; 
 scalar_t__ LASTLINE (TYPE_2__*) ; 
 scalar_t__ SCROLL_W_QUIT ; 
 int /*<<< orphan*/ * TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* VIP (TYPE_2__*) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 
 int /*<<< orphan*/  vs_wait (TYPE_2__*,int*,scalar_t__) ; 

__attribute__((used)) static void
vs_scroll(SCR *sp, int *continuep, sw_t wtype)
{
	GS *gp;
	VI_PRIVATE *vip;

	gp = sp->gp;
	vip = VIP(sp);
	if (!IS_ONELINE(sp)) {
		/*
		 * Scroll the screen.  Instead of scrolling the entire screen,
		 * delete the line above the first line output so preserve the
		 * maximum amount of the screen.
		 */
		(void)gp->scr_move(sp, vip->totalcount <
		    sp->rows ? LASTLINE(sp) - vip->totalcount : 0, 0);
		(void)gp->scr_deleteln(sp);

		/* If there are screens below us, push them back into place. */
		if (TAILQ_NEXT(sp, q) != NULL) {
			(void)gp->scr_move(sp, LASTLINE(sp), 0);
			(void)gp->scr_insertln(sp);
		}
	}
	if (wtype == SCROLL_W_QUIT && vip->linecount < sp->t_maxrows)
		return;
	vs_wait(sp, continuep, wtype);
}