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
typedef  int u_long ;
struct TYPE_5__ {int count; int /*<<< orphan*/  m_final; int /*<<< orphan*/  m_start; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ INTERRUPTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_BUFFER ; 
 int /*<<< orphan*/  VC_C1SET ; 
 int /*<<< orphan*/  VC_ISDOT ; 
 int /*<<< orphan*/  inc_buf (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
v_put(SCR *sp, VICMD *vp)
{
	u_long cnt;

	if (F_ISSET(vp, VC_ISDOT))
		inc_buf(sp, vp);

	/*
	 * !!!
	 * Historic vi did not support a count with the 'p' and 'P'
	 * commands.  It's useful, so we do.
	 */
	for (cnt = F_ISSET(vp, VC_C1SET) ? vp->count : 1; cnt--;) {
		if (put(sp, NULL,
		    F_ISSET(vp, VC_BUFFER) ? &vp->buffer : NULL,
		    &vp->m_start, &vp->m_final, 1))
			return (1);
		vp->m_start = vp->m_final;
		if (INTERRUPTED(sp))
			return (1);
	}
	return (0);
}