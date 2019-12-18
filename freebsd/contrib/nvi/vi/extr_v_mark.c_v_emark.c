#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int e_lno; scalar_t__ e_cno; } ;
struct TYPE_15__ {int /*<<< orphan*/  cno; int /*<<< orphan*/  lno; } ;
struct TYPE_16__ {TYPE_1__ ev; TYPE_2__ m_stop; } ;
typedef  TYPE_3__ VICMD ;
struct TYPE_18__ {int cols; } ;
struct TYPE_17__ {int soff; int /*<<< orphan*/  lno; } ;
typedef  TYPE_4__ SMAP ;
typedef  TYPE_5__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  BQMARK ; 
 TYPE_4__* HMAP ; 
 int /*<<< orphan*/  M_BERR ; 
 TYPE_4__* TMAP ; 
 int mark (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vs_colpos (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 

int
v_emark(SCR *sp, VICMD *vp)
{
	SMAP *smp;

	smp = HMAP + vp->ev.e_lno;
	if (smp > TMAP) {
		msgq(sp, M_BERR, "320|Unknown cursor position.");
		return (1);
	}
	vp->m_stop.lno = smp->lno;
	vp->m_stop.cno =
	    vs_colpos(sp, smp->lno, vp->ev.e_cno + (smp->soff - 1) * sp->cols);
	return (mark(sp, vp, 0, BQMARK));
}