#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cno; int /*<<< orphan*/  lno; } ;
struct TYPE_6__ {TYPE_1__ m_stop; TYPE_1__ m_final; TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 scalar_t__ nonblank (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  v_sol (int /*<<< orphan*/ *) ; 

int
v_first(SCR *sp, VICMD *vp)
{
	/*
	 * !!!
	 * Yielding to none in our quest for compatibility with every
	 * historical blemish of vi, no matter how strange it might be,
	 * we permit the user to enter a count and then ignore it.
	 */

	/*
	 * Move to the first non-blank.
	 *
	 * Can't just use RCM_SET_FNB, in case ^ is used as the motion
	 * component of another command.
	 */
	vp->m_stop.cno = 0;
	if (nonblank(sp, vp->m_stop.lno, &vp->m_stop.cno))
		return (1);

	/*
	 * !!!
	 * The ^ command succeeded if used as a command when the cursor was
	 * on the first non-blank in the line, but failed if used as a motion
	 * component in the same situation.
	 */
	if (ISMOTION(vp) && vp->m_start.cno == vp->m_stop.cno) {
		v_sol(sp);
		return (1);
	}

	/*
	 * If moving right, non-motion commands move to the end of the range.
	 * Delete and yank stay at the start.  Motion commands adjust the
	 * ending point to the character before the current ending charcter.
	 *
	 * If moving left, all commands move to the end of the range.  Motion
	 * commands adjust the starting point to the character before the
	 * current starting character.
	 */
	if (vp->m_start.cno < vp->m_stop.cno)
		if (ISMOTION(vp)) {
			--vp->m_stop.cno;
			vp->m_final = vp->m_start;
		} else
			vp->m_final = vp->m_stop;
	else {
		if (ISMOTION(vp))
			--vp->m_start.cno;
		vp->m_final = vp->m_stop;
	}
	return (0);
}