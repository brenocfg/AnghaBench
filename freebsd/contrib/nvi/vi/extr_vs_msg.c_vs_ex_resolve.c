#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sw_t ;
struct TYPE_20__ {scalar_t__ lcontinue; int totalcount; int rows; scalar_t__ linecount; TYPE_3__* gp; int /*<<< orphan*/  mtype; } ;
typedef  TYPE_1__ VI_PRIVATE ;
struct TYPE_22__ {int e_flno; int e_tlno; int /*<<< orphan*/  e_event; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* scr_attr ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;scalar_t__ (* scr_screen ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_3__ GS ;
typedef  TYPE_4__ EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  E_REPAINT ; 
 int /*<<< orphan*/  F_CLR (TYPE_1__*,int) ; 
 scalar_t__ F_ISSET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERRUPTED (TYPE_1__*) ; 
 int /*<<< orphan*/  M_NONE ; 
 int /*<<< orphan*/  SA_ALTERNATE ; 
 int /*<<< orphan*/  SCROLL_W ; 
 int /*<<< orphan*/  SCROLL_W_EX ; 
 int SC_EXIT ; 
 int SC_EXIT_FORCE ; 
 int SC_EX_WAIT_NO ; 
 int SC_EX_WAIT_YES ; 
 int SC_FSWITCH ; 
 int SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  SC_SCR_REDRAW ; 
 int /*<<< orphan*/  SC_SCR_REFORMAT ; 
 int SC_SSWITCH ; 
 int /*<<< orphan*/  SC_VI ; 
 int /*<<< orphan*/ * TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* VIP (TYPE_1__*) ; 
 int /*<<< orphan*/  VIP_CUR_INVALID ; 
 int /*<<< orphan*/  VIP_N_EX_PAINT ; 
 int VIP_N_EX_REDRAW ; 
 int /*<<< orphan*/  q ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vs_output (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vs_repaint (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  vs_scroll (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vs_wait (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 

int
vs_ex_resolve(SCR *sp, int *continuep)
{
	EVENT ev;
	GS *gp;
	VI_PRIVATE *vip;
	sw_t wtype;

	gp = sp->gp;
	vip = VIP(sp);
	*continuep = 0;

	/* If we ran any ex command, we can't trust the cursor position. */
	F_SET(vip, VIP_CUR_INVALID);

	/* Terminate any partially written message. */
	if (vip->lcontinue != 0) {
		vs_output(sp, vip->mtype, ".", 1);
		vip->lcontinue = 0;

		vip->mtype = M_NONE;
	}

	/*
	 * If we switched out of the vi screen into ex, switch back while we
	 * figure out what to do with the screen and potentially get another
	 * command to execute.
	 *
	 * If we didn't switch into ex, we're not required to wait, and less
	 * than 2 lines of output, we can continue without waiting for the
	 * wait.
	 *
	 * Note, all other code paths require waiting, so we leave the report
	 * of modified lines until later, so that we won't wait for no other
	 * reason than a threshold number of lines were modified.  This means
	 * we display cumulative line modification reports for groups of ex
	 * commands.  That seems right to me (well, at least not wrong).
	 */
	if (F_ISSET(sp, SC_SCR_EXWROTE)) {
		if (sp->gp->scr_screen(sp, SC_VI))
			return (1);
	} else
		if (!F_ISSET(sp, SC_EX_WAIT_YES) && vip->totalcount < 2) {
			F_CLR(sp, SC_EX_WAIT_NO);
			return (0);
		}

	/* Clear the required wait flag, it's no longer needed. */
	F_CLR(sp, SC_EX_WAIT_YES);

	/*
	 * Wait, unless explicitly told not to wait or the user interrupted
	 * the command.  If the user is leaving the screen, for any reason,
	 * they can't continue with further ex commands.
	 */
	if (!F_ISSET(sp, SC_EX_WAIT_NO) && !INTERRUPTED(sp)) {
		wtype = F_ISSET(sp, SC_EXIT | SC_EXIT_FORCE |
		    SC_FSWITCH | SC_SSWITCH) ? SCROLL_W : SCROLL_W_EX;
		if (F_ISSET(sp, SC_SCR_EXWROTE))
			vs_wait(sp, continuep, wtype);
		else
			vs_scroll(sp, continuep, wtype);
		if (*continuep)
			return (0);
	}

	/* If ex wrote on the screen, refresh the screen image. */
	if (F_ISSET(sp, SC_SCR_EXWROTE))
		F_SET(vip, VIP_N_EX_PAINT);

	/*
	 * If we're not the bottom of the split screen stack, the screen
	 * image itself is wrong, so redraw everything.
	 */
	if (TAILQ_NEXT(sp, q) != NULL)
		F_SET(sp, SC_SCR_REDRAW);

	/* If ex changed the underlying file, the map itself is wrong. */
	if (F_ISSET(vip, VIP_N_EX_REDRAW))
		F_SET(sp, SC_SCR_REFORMAT);

	/* Ex may have switched out of the alternate screen, return. */
	(void)gp->scr_attr(sp, SA_ALTERNATE, 1);

	/*
	 * Whew.  We're finally back home, after what feels like years.
	 * Kiss the ground.
	 */
	F_CLR(sp, SC_SCR_EXWROTE | SC_EX_WAIT_NO);

	/*
	 * We may need to repaint some of the screen, e.g.:
	 *
	 *	:set
	 *	:!ls
	 *
	 * gives us a combination of some lines that are "wrong", and a need
	 * for a full refresh.
	 */
	if (vip->totalcount > 1) {
		/* Set up the redraw of the overwritten lines. */
		ev.e_event = E_REPAINT;
		ev.e_flno = vip->totalcount >=
		    sp->rows ? 1 : sp->rows - vip->totalcount;
		ev.e_tlno = sp->rows;

		/* Reset the count of overwriting lines. */
		vip->linecount = vip->lcontinue = vip->totalcount = 0;

		/* Redraw. */
		(void)vs_repaint(sp, &ev);
	} else
		/* Reset the count of overwriting lines. */
		vip->linecount = vip->lcontinue = vip->totalcount = 0;

	return (0);
}