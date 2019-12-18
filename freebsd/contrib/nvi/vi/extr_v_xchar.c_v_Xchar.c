#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_12__ {int /*<<< orphan*/  cno; } ;
struct TYPE_11__ {int cno; } ;
struct TYPE_9__ {int cno; } ;
struct TYPE_10__ {int count; TYPE_5__ m_stop; TYPE_4__ m_start; int /*<<< orphan*/  buffer; TYPE_1__ m_final; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_BUFFER ; 
 int /*<<< orphan*/  VC_C1SET ; 
 scalar_t__ cut (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int del (int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_sol (int /*<<< orphan*/ *) ; 

int
v_Xchar(SCR *sp, VICMD *vp)
{
	u_long cnt;

	if (vp->m_start.cno == 0) {
		v_sol(sp);
		return (1);
	}

	cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	if (cnt >= vp->m_start.cno)
		vp->m_start.cno = 0;
	else
		vp->m_start.cno -= cnt;
	--vp->m_stop.cno;
	vp->m_final.cno = vp->m_start.cno;

	if (cut(sp,
	    F_ISSET(vp, VC_BUFFER) ? &vp->buffer : NULL,
	    &vp->m_start, &vp->m_stop, 0))
		return (1);
	return (del(sp, &vp->m_start, &vp->m_stop, 0));
}