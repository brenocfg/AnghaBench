#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
struct TYPE_9__ {int count; int /*<<< orphan*/  m_stop; int /*<<< orphan*/  m_final; } ;
typedef  TYPE_1__ VICMD ;
struct TYPE_10__ {int /*<<< orphan*/  t_maxrows; } ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_B ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SPLIT (TYPE_2__*) ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int O_VAL (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_WINDOW ; 
 int /*<<< orphan*/  VC_C1SET ; 
 scalar_t__ vs_sm_scroll (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
v_pageup(SCR *sp, VICMD *vp)
{
	recno_t offset;

	/*
	 * !!!
	 * The calculation in IEEE Std 1003.2-1992 (POSIX) is:
	 *
	 *	top_line = top_line - count * (window - 2);
	 *
	 * which was historically wrong.  The correct one is:
	 *
	 *	top_line = (top_line - count * window) + 2;
	 *
	 * A simpler expression is that, as with ^F, we scroll exactly:
	 *
	 *	count * window - 2
	 *
	 * lines.
	 *
	 * Bizarre.  As with ^F, an overlap makes no sense for anything
	 * but the first screen.  We do it the historical way as there's
	 * no good reason to change it.
	 *
	 * If the screen has been split horizontally, use the smaller of
	 * the current window size and the window option value.
	 *
	 * It possible for this calculation to be less than 1; move at
	 * least one line.
	 */
	offset = (F_ISSET(vp, VC_C1SET) ? vp->count : 1) * (IS_SPLIT(sp) ?
	    MIN(sp->t_maxrows, O_VAL(sp, O_WINDOW)) : O_VAL(sp, O_WINDOW));
	offset = offset <= 2 ? 1 : offset - 2;
	if (vs_sm_scroll(sp, &vp->m_stop, offset, CNTRL_B))
		return (1);
	vp->m_final = vp->m_stop;
	return (0);
}