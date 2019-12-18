#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cno; int /*<<< orphan*/  lno; } ;
struct TYPE_7__ {int count; TYPE_1__ m_stop; TYPE_1__ m_final; TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  v_nomove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_sol (int /*<<< orphan*/ *) ; 
 scalar_t__ vs_colpos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int
v_ncol(SCR *sp, VICMD *vp)
{
	if (F_ISSET(vp, VC_C1SET) && vp->count > 1) {
		--vp->count;
		vp->m_stop.cno =
		    vs_colpos(sp, vp->m_start.lno, (size_t)vp->count);
		/*
		 * !!!
		 * The | command succeeded if used as a command and the cursor
		 * didn't move, but failed if used as a motion component in the
		 * same situation.
		 */
		if (ISMOTION(vp) && vp->m_stop.cno == vp->m_start.cno) {
			v_nomove(sp);
			return (1);
		}
	} else {
		/*
		 * !!!
		 * The | command succeeded if used as a command in column 0
		 * without a count, but failed if used as a motion component
		 * in the same situation.
		 */
		if (ISMOTION(vp) && vp->m_start.cno == 0) {
			v_sol(sp);
			return (1);
		}
		vp->m_stop.cno = 0;
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