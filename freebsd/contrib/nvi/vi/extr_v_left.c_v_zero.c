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
struct TYPE_7__ {scalar_t__ cno; } ;
struct TYPE_6__ {scalar_t__ cno; } ;
struct TYPE_8__ {TYPE_2__ m_stop; TYPE_2__ m_final; TYPE_1__ m_start; } ;
typedef  TYPE_3__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ ISMOTION (TYPE_3__*) ; 
 int /*<<< orphan*/  v_sol (int /*<<< orphan*/ *) ; 

int
v_zero(SCR *sp, VICMD *vp)
{
	/*
	 * !!!
	 * The 0 command succeeded if used as a command in the first column
	 * but failed if used as a motion component in the same situation.
	 */
	if (ISMOTION(vp) && vp->m_start.cno == 0) {
		v_sol(sp);
		return (1);
	}

	/*
	 * All commands move to the end of the range.  Motion commands
	 * adjust the starting point to the character before the current
	 * one.
	 */
	vp->m_stop.cno = 0;
	if (ISMOTION(vp))
		--vp->m_start.cno;
	vp->m_final = vp->m_stop;
	return (0);
}