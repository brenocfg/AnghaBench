#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
struct TYPE_6__ {int lno; } ;
struct TYPE_8__ {int lno; } ;
struct TYPE_7__ {int count; TYPE_1__ m_stop; TYPE_1__ m_final; TYPE_4__ m_start; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  v_sof (int /*<<< orphan*/ *,TYPE_4__*) ; 

int
v_up(SCR *sp, VICMD *vp)
{
	recno_t lno;

	lno = F_ISSET(vp, VC_C1SET) ? vp->count : 1;
	if (vp->m_start.lno <= lno) {
		v_sof(sp, &vp->m_start);
		return (1);
	}
	vp->m_stop.lno = vp->m_start.lno - lno;
	vp->m_final = vp->m_stop;
	return (0);
}