#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct interface {int int_state; int /*<<< orphan*/  int_act_time; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ CHECK_BAD_INTERVAL ; 
 int IS_BROKE ; 
 int IS_SICK ; 
 int /*<<< orphan*/  LIM_SEC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NEVER ; 
 int /*<<< orphan*/  ifinit_timer ; 
 TYPE_1__ now ; 
 int /*<<< orphan*/  trace_if (char*,struct interface*) ; 

void
if_sick(struct interface *ifp)
{
	if (0 == (ifp->int_state & (IS_SICK | IS_BROKE))) {
		ifp->int_state |= IS_SICK;
		ifp->int_act_time = NEVER;
		trace_if("Chg", ifp);

		LIM_SEC(ifinit_timer, now.tv_sec+CHECK_BAD_INTERVAL);
	}
}