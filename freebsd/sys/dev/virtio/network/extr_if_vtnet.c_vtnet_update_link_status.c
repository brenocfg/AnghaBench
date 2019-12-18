#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vtnet_softc {int vtnet_link_active; struct ifnet* vtnet_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK_ASSERT (struct vtnet_softc*) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int vtnet_is_link_up (struct vtnet_softc*) ; 

__attribute__((used)) static void
vtnet_update_link_status(struct vtnet_softc *sc)
{
	struct ifnet *ifp;
	int link;

	ifp = sc->vtnet_ifp;

	VTNET_CORE_LOCK_ASSERT(sc);
	link = vtnet_is_link_up(sc);

	/* Notify if the link status has changed. */
	if (link != 0 && sc->vtnet_link_active == 0) {
		sc->vtnet_link_active = 1;
		if_link_state_change(ifp, LINK_STATE_UP);
	} else if (link == 0 && sc->vtnet_link_active != 0) {
		sc->vtnet_link_active = 0;
		if_link_state_change(ifp, LINK_STATE_DOWN);
	}
}