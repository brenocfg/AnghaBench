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
struct ifnet {int if_drv_flags; } ;
struct bridge_softc {int /*<<< orphan*/  sc_stp; int /*<<< orphan*/  sc_brcallout; struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  BRIDGE_UNLOCK (struct bridge_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int bridge_rtable_prune_period ; 
 int /*<<< orphan*/  bridge_timer ; 
 int /*<<< orphan*/  bstp_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct bridge_softc*) ; 
 int hz ; 

__attribute__((used)) static void
bridge_init(void *xsc)
{
	struct bridge_softc *sc = (struct bridge_softc *)xsc;
	struct ifnet *ifp = sc->sc_ifp;

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	BRIDGE_LOCK(sc);
	callout_reset(&sc->sc_brcallout, bridge_rtable_prune_period * hz,
	    bridge_timer, sc);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	bstp_init(&sc->sc_stp);		/* Initialize Spanning Tree */

	BRIDGE_UNLOCK(sc);
}