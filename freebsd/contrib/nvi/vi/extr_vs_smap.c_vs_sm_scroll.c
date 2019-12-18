#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int scroll_t ;
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_5__ {scalar_t__ cno; int /*<<< orphan*/  lno; } ;
typedef  int /*<<< orphan*/  SMAP ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ MARK ;

/* Variables and functions */
#define  CNTRL_B 135 
#define  CNTRL_D 134 
#define  CNTRL_E 133 
#define  CNTRL_F 132 
#define  CNTRL_U 131 
#define  CNTRL_Y 130 
 int /*<<< orphan*/  F_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIP_CUR_INVALID ; 
#define  Z_CARAT 129 
#define  Z_PLUS 128 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ nonblank (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ vs_sm_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vs_sm_down (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vs_sm_up (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
vs_sm_scroll(SCR *sp, MARK *rp, recno_t count, scroll_t scmd)
{
	SMAP *smp;

	/*
	 * Invalidate the cursor.  The line is probably going to change,
	 * (although for ^E and ^Y it may not).  In any case, the scroll
	 * routines move the cursor to draw things.
	 */
	F_SET(VIP(sp), VIP_CUR_INVALID);

	/* Find the cursor in the screen. */
	if (vs_sm_cursor(sp, &smp))
		return (1);

	switch (scmd) {
	case CNTRL_B:
	case CNTRL_U:
	case CNTRL_Y:
	case Z_CARAT:
		if (vs_sm_down(sp, rp, count, scmd, smp))
			return (1);
		break;
	case CNTRL_D:
	case CNTRL_E:
	case CNTRL_F:
	case Z_PLUS:
		if (vs_sm_up(sp, rp, count, scmd, smp))
			return (1);
		break;
	default:
		abort();
	}

	/*
	 * !!!
	 * If we're at the start of a line, go for the first non-blank.
	 * This makes it look like the old vi, even though we're moving
	 * around by logical lines, not physical ones.
	 *
	 * XXX
	 * In the presence of a long line, which has more than a screen
	 * width of leading spaces, this code can cause a cursor warp.
	 * Live with it.
	 */
	if (scmd != CNTRL_E && scmd != CNTRL_Y &&
	    rp->cno == 0 && nonblank(sp, rp->lno, &rp->cno))
		return (1);

	return (0);
}