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
struct TYPE_5__ {int link_status; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct oce_async_cqe_link_state {TYPE_2__ u0; } ;
struct TYPE_7__ {int link_status; int /*<<< orphan*/  ifp; } ;
typedef  TYPE_3__* POCE_SOFTC ;

/* Variables and functions */
 int ASYNC_EVENT_LINK_DOWN ; 
 int ASYNC_EVENT_LINK_UP ; 
 int ASYNC_EVENT_LOGICAL ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_link_state(POCE_SOFTC sc, struct oce_async_cqe_link_state *acqe)
{
	/* Update Link status */
	if ((acqe->u0.s.link_status & ~ASYNC_EVENT_LOGICAL) ==
	     ASYNC_EVENT_LINK_UP) {
		sc->link_status = ASYNC_EVENT_LINK_UP;
		if_link_state_change(sc->ifp, LINK_STATE_UP);
	} else {
		sc->link_status = ASYNC_EVENT_LINK_DOWN;
		if_link_state_change(sc->ifp, LINK_STATE_DOWN);
	}
}