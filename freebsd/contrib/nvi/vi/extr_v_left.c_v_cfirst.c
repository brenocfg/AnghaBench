#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
struct TYPE_8__ {scalar_t__ cno; int lno; } ;
struct TYPE_9__ {int count; TYPE_1__ m_stop; TYPE_1__ m_start; int /*<<< orphan*/  rkp; TYPE_1__ m_final; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISCMD (int /*<<< orphan*/ ,char) ; 
 scalar_t__ ISMOTION (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VM_LMODE ; 
 scalar_t__ db_last (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ nonblank (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int v_down (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  v_sol (int /*<<< orphan*/ *) ; 

int
v_cfirst(SCR *sp, VICMD *vp)
{
	recno_t cnt, lno;

	/*
	 * !!!
	 * If the _ is a motion component, it makes the command a line motion
	 * e.g. "d_" deletes the line.  It also means that the cursor doesn't
	 * move.
	 *
	 * The _ command never failed in the first column.
	 */
	if (ISMOTION(vp))
		F_SET(vp, VM_LMODE);
	/*
	 * !!!
	 * Historically a specified count makes _ move down count - 1
	 * rows, so, "3_" is the same as "2j_".
	 */
	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	if (cnt != 1) {
		--vp->count;
		return (v_down(sp, vp));
	}

	/*
	 * Move to the first non-blank.
	 *
	 * Can't just use RCM_SET_FNB, in case _ is used as the motion
	 * component of another command.
	 */
	vp->m_stop.cno = 0;
	if (nonblank(sp, vp->m_stop.lno, &vp->m_stop.cno))
		return (1);

	/*
	 * !!!
	 * The _ command has to fail if the file is empty and we're doing
	 * a delete.  If deleting line 1, and 0 is the first nonblank,
	 * make the check.
	 */
	if (vp->m_stop.lno == 1 &&
	    vp->m_stop.cno == 0 && ISCMD(vp->rkp, 'd')) {
		if (db_last(sp, &lno))
			return (1);
		if (lno == 0) {
			v_sol(sp);
			return (1);
		}
	}

	/*
	 * Delete and non-motion commands move to the end of the range,
	 * yank stays at the start.  Ignore others.
	 */
	vp->m_final =
	    ISMOTION(vp) && ISCMD(vp->rkp, 'y') ? vp->m_start : vp->m_stop;
	return (0);
}