#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t cno; int /*<<< orphan*/  lno; } ;
struct TYPE_16__ {scalar_t__ lno; } ;
struct TYPE_17__ {scalar_t__ lno; } ;
struct TYPE_14__ {TYPE_1__ m_final; TYPE_8__ m_start; TYPE_9__ m_stop; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_15__ {int /*<<< orphan*/ * rptlines; } ;
typedef  TYPE_3__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  CUT_LINEMODE ; 
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t L_YANKED ; 
 int /*<<< orphan*/  VC_BUFFER ; 
 int /*<<< orphan*/  VM_LMODE ; 
 int /*<<< orphan*/  VM_RCM_MASK ; 
 int /*<<< orphan*/  VM_RCM_SET ; 
 scalar_t__ cut (TYPE_3__*,int /*<<< orphan*/ *,TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ db_get (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

int
v_yank(SCR *sp, VICMD *vp)
{
	size_t len;

	if (cut(sp,
	    F_ISSET(vp, VC_BUFFER) ? &vp->buffer : NULL, &vp->m_start,
	    &vp->m_stop, F_ISSET(vp, VM_LMODE) ? CUT_LINEMODE : 0))
		return (1);
	sp->rptlines[L_YANKED] += (vp->m_stop.lno - vp->m_start.lno) + 1;

	/*
	 * One special correction, in case we've deleted the current line or
	 * character.  We check it here instead of checking in every command
	 * that can be a motion component.
	 */
	if (db_get(sp, vp->m_final.lno, DBG_FATAL, NULL, &len))
		return (1);

	/*
	 * !!!
	 * Cursor movements, other than those caused by a line mode command
	 * moving to another line, historically reset the relative position.
	 *
	 * This currently matches the check made in v_delete(), I'm hoping
	 * that they should be consistent...
	 */  
	if (!F_ISSET(vp, VM_LMODE)) {
		F_CLR(vp, VM_RCM_MASK);
		F_SET(vp, VM_RCM_SET);

		/* Make sure the set cursor position exists. */
		if (vp->m_final.cno >= len)
			vp->m_final.cno = len ? len - 1 : 0;
	}
	return (0);
}