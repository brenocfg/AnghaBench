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
struct TYPE_6__ {int lno; } ;
struct TYPE_7__ {int count; TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  C_JOIN ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  ex_cinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int v_exec_ex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

int
v_join(SCR *sp, VICMD *vp)
{
	EXCMD cmd;
	int lno;

	/*
	 * YASC.
	 * The general rule is that '#J' joins # lines, counting the current
	 * line.  However, 'J' and '1J' are the same as '2J', i.e. join the
	 * current and next lines.  This doesn't map well into the ex command
	 * (which takes two line numbers), so we handle it here.  Note that
	 * we never test for EOF -- historically going past the end of file
	 * worked just fine.
	 */
	lno = vp->m_start.lno + 1;
	if (F_ISSET(vp, VC_C1SET) && vp->count > 2)
		lno = vp->m_start.lno + (vp->count - 1);

	ex_cinit(sp, &cmd, C_JOIN, 2, vp->m_start.lno, lno, 0);
	return (v_exec_ex(sp, vp, &cmd));
}