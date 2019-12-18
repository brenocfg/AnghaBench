#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int lundo; int /*<<< orphan*/  m_final; } ;
typedef  TYPE_1__ VICMD ;
struct TYPE_14__ {int /*<<< orphan*/  u_ccnt; } ;
struct TYPE_13__ {TYPE_1__* ep; int /*<<< orphan*/  ccnt; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_1__ EXF ;

/* Variables and functions */
#define  BACKWARD 129 
#define  FORWARD 128 
 int /*<<< orphan*/  F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_UNDO ; 
 int /*<<< orphan*/  VC_ISDOT ; 
 TYPE_8__* VIP (TYPE_2__*) ; 
 int /*<<< orphan*/  abort () ; 
 int log_backward (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int log_forward (TYPE_2__*,int /*<<< orphan*/ *) ; 

int
v_undo(SCR *sp, VICMD *vp)
{
	EXF *ep;

	/* Set the command count. */
	VIP(sp)->u_ccnt = sp->ccnt;

	/*
	 * !!!
	 * In historic vi, 'u' toggled between "undo" and "redo", i.e. 'u'
	 * undid the last undo.  However, if there has been a change since
	 * the last undo/redo, we always do an undo.  To make this work when
	 * the user can undo multiple operations, we leave the old semantic
	 * unchanged, but make '.' after a 'u' do another undo/redo operation.
	 * This has two problems.
	 *
	 * The first is that 'u' didn't set '.' in historic vi.  So, if a
	 * user made a change, realized it was in the wrong place, does a
	 * 'u' to undo it, moves to the right place and then does '.', the
	 * change was reapplied.  To make this work, we only apply the '.'
	 * to the undo command if it's the command immediately following an
	 * undo command.  See vi/vi.c:getcmd() for the details.
	 *
	 * The second is that the traditional way to view the numbered cut
	 * buffers in vi was to enter the commands "1pu.u.u.u. which will
	 * no longer work because the '.' immediately follows the 'u' command.
	 * Since we provide a much better method of viewing buffers, and
	 * nobody can think of a better way of adding in multiple undo, this
	 * remains broken.
	 *
	 * !!!
	 * There is change to historic practice for the final cursor position
	 * in this implementation.  In historic vi, if an undo was isolated to
	 * a single line, the cursor moved to the start of the change, and
	 * then, subsequent 'u' commands would not move it again. (It has been
	 * pointed out that users used multiple undo commands to get the cursor
	 * to the start of the changed text.)  Nvi toggles between the cursor
	 * position before and after the change was made.  One final issue is
	 * that historic vi only did this if the user had not moved off of the
	 * line before entering the undo command; otherwise, vi would move the
	 * cursor to the most attractive position on the changed line.
	 *
	 * It would be difficult to match historic practice in this area. You
	 * not only have to know that the changes were isolated to one line,
	 * but whether it was the first or second undo command as well.  And,
	 * to completely match historic practice, we'd have to track users line
	 * changes, too.  This isn't worth the effort.
	 */
	ep = sp->ep;
	if (!F_ISSET(ep, F_UNDO)) {
		F_SET(ep, F_UNDO);
		ep->lundo = BACKWARD;
	} else if (!F_ISSET(vp, VC_ISDOT))
		ep->lundo = ep->lundo == BACKWARD ? FORWARD : BACKWARD;

	switch (ep->lundo) {
	case BACKWARD:
		return (log_backward(sp, &vp->m_final));
	case FORWARD:
		return (log_forward(sp, &vp->m_final));
	default:
		abort();
	}
	/* NOTREACHED */
}