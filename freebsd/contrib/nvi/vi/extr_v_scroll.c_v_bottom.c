#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ count; int /*<<< orphan*/  m_stop; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_BOTTOM ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  goto_adjust (TYPE_1__*) ; 
 scalar_t__ vs_sm_position (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

int
v_bottom(SCR *sp, VICMD *vp)
{
	if (vs_sm_position(sp, &vp->m_stop,
	    F_ISSET(vp, VC_C1SET) ? vp->count - 1 : 0, P_BOTTOM))
		return (1);
	goto_adjust(vp);
	return (0);
}