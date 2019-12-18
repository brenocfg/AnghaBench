#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; int /*<<< orphan*/  m_stop; int /*<<< orphan*/  m_final; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_E ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_C1SET ; 
 scalar_t__ vs_sm_scroll (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
v_linedown(SCR *sp, VICMD *vp)
{
	/*
	 * The cursor moves up, staying with its original line, unless it
	 * reaches the top of the screen.
	 */
	if (vs_sm_scroll(sp,
	    &vp->m_stop, F_ISSET(vp, VC_C1SET) ? vp->count : 1, CNTRL_E))
		return (1);
	vp->m_final = vp->m_stop;
	return (0);
}