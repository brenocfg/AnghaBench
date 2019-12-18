#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ lno; scalar_t__ cno; } ;
struct TYPE_8__ {TYPE_1__ m_start; TYPE_1__ m_final; TYPE_1__ m_stop; int /*<<< orphan*/  rkp; } ;
typedef  TYPE_2__ VICMD ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISCMD (int /*<<< orphan*/ ,char) ; 
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_RCM_MASK ; 
 int /*<<< orphan*/  VM_RCM_SETFNB ; 

__attribute__((used)) static void
goto_adjust(VICMD *vp)
{
	/* Guess that it's the end of the range. */
	vp->m_final = vp->m_stop;

	/*
	 * Non-motion commands move the cursor to the end of the range, and
	 * then to the NEXT nonblank of the line.  Historic vi always moved
	 * to the first nonblank in the line; since the H, M, and L commands
	 * are logical motions in this implementation, we do the next nonblank
	 * so that it looks approximately the same to the user.  To make this
	 * happen, the VM_RCM_SETNNB flag is set in the vcmd.c command table.
	 *
	 * If it's a motion, it's more complicated.  The best possible solution
	 * is probably to display the first nonblank of the line the cursor
	 * will eventually rest on.  This is tricky, particularly given that if
	 * the associated command is a delete, we don't yet know what line that
	 * will be.  So, we clear the VM_RCM_SETNNB flag, and set the first
	 * nonblank flag (VM_RCM_SETFNB).  Note, if the lines are sufficiently
	 * long, this can cause the cursor to warp out of the screen.  It's too
	 * hard to fix.
	 *
	 * XXX
	 * The G command is always first nonblank, so it's okay to reset it.
	 */
	if (ISMOTION(vp)) {
		F_CLR(vp, VM_RCM_MASK);
		F_SET(vp, VM_RCM_SETFNB);
	} else
		return;

	/*
	 * If moving backward in the file, delete and yank move to the end
	 * of the range, unless the line didn't change, in which case yank
	 * doesn't move.  If moving forward in the file, delete and yank
	 * stay at the start of the range.  Ignore others.
	 */
	if (vp->m_stop.lno < vp->m_start.lno ||
	    (vp->m_stop.lno == vp->m_start.lno &&
	    vp->m_stop.cno < vp->m_start.cno)) {
		if (ISCMD(vp->rkp, 'y') && vp->m_stop.lno == vp->m_start.lno)
			vp->m_final = vp->m_start;
	} else
		vp->m_final = vp->m_start;
}