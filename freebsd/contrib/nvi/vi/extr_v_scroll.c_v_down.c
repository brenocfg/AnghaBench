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
typedef  scalar_t__ recno_t ;
struct TYPE_7__ {scalar_t__ lno; } ;
struct TYPE_6__ {int count; TYPE_2__ m_stop; TYPE_2__ m_start; TYPE_2__ m_final; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISMOTION (TYPE_1__*) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  db_exist (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  v_eof (int /*<<< orphan*/ *,TYPE_2__*) ; 

int
v_down(SCR *sp, VICMD *vp)
{
	recno_t lno;

	lno = vp->m_start.lno + (F_ISSET(vp, VC_C1SET) ? vp->count : 1);
	if (!db_exist(sp, lno)) {
		v_eof(sp, &vp->m_start);
		return (1);
	}
	vp->m_stop.lno = lno;
	vp->m_final = ISMOTION(vp) ? vp->m_start : vp->m_stop;
	return (0);
}