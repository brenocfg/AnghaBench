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
struct TYPE_4__ {int /*<<< orphan*/  m_stop; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  P_MIDDLE ; 
 int /*<<< orphan*/  goto_adjust (TYPE_1__*) ; 
 scalar_t__ vs_sm_position (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
v_middle(SCR *sp, VICMD *vp)
{
	/*
	 * Yielding to none in our quest for compatibility with every
	 * historical blemish of vi, no matter how strange it might be,
	 * we permit the user to enter a count and then ignore it.
	 */
	if (vs_sm_position(sp, &vp->m_stop, 0, P_MIDDLE))
		return (1);
	goto_adjust(vp);
	return (0);
}