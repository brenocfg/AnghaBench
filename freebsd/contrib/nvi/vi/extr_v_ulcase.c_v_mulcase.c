#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
struct TYPE_6__ {scalar_t__ lno; size_t cno; } ;
struct TYPE_7__ {scalar_t__ lno; int /*<<< orphan*/  cno; } ;
struct TYPE_8__ {TYPE_1__ m_stop; TYPE_2__ m_start; } ;
typedef  TYPE_3__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_LMODE ; 
 scalar_t__ db_get (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ulcase (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t) ; 

int
v_mulcase(SCR *sp, VICMD *vp)
{
	CHAR_T *p;
	size_t len;
	recno_t lno;

	for (lno = vp->m_start.lno;;) {
		if (db_get(sp, lno, DBG_FATAL, &p, &len))
			return (1);
		if (len != 0 && ulcase(sp, lno, p, len,
		    lno == vp->m_start.lno ? vp->m_start.cno : 0,
		    !F_ISSET(vp, VM_LMODE) &&
		    lno == vp->m_stop.lno ? vp->m_stop.cno : len))
			return (1);

		if (++lno > vp->m_stop.lno)
			break;
	}

	/*
	 * XXX
	 * I didn't create a new motion command when I added motion semantics
	 * for ~.  While that's the correct way to do it, that choice would
	 * have required changes all over the vi directory for little gain.
	 * Instead, we pretend it's a yank command.  Note, this means that we
	 * follow the cursor motion rules for yank commands, but that seems
	 * reasonable to me.
	 */
	return (0);
}