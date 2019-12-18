#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_7__ {scalar_t__ i_cnt; size_t i_next; TYPE_1__* i_event; } ;
struct TYPE_6__ {TYPE_3__* gp; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_ch; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ GS ;

/* Variables and functions */
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QREM (int) ; 

int
v_event_flush(
	SCR *sp,
	u_int flags)
{
	GS *gp;
	int rval;

	for (rval = 0, gp = sp->gp; gp->i_cnt != 0 &&
	    F_ISSET(&gp->i_event[gp->i_next].e_ch, flags); rval = 1)
		QREM(1);
	return (rval);
}