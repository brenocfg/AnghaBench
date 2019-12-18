#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  m_stop; int /*<<< orphan*/  m_final; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ VICMD ;
struct TYPE_8__ {int /*<<< orphan*/  defscroll; } ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_D ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 scalar_t__ vs_sm_scroll (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
v_hpagedown(SCR *sp, VICMD *vp)
{
	/*
	 * Half screens always succeed unless already at EOF.
	 *
	 * !!!
	 * Half screens set the scroll value, even if the command
	 * ultimately failed, in historic vi.  Probably a don't care.
	 */
	if (F_ISSET(vp, VC_C1SET))
		sp->defscroll = vp->count;
	if (vs_sm_scroll(sp, &vp->m_stop, sp->defscroll, CNTRL_D))
		return (1);
	vp->m_final = vp->m_stop;
	return (0);
}