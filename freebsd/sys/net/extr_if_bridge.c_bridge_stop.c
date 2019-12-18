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
struct ifnet {int if_drv_flags; struct bridge_softc* if_softc; } ;
struct bridge_softc {int /*<<< orphan*/  sc_stp; int /*<<< orphan*/  sc_brcallout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT (struct bridge_softc*) ; 
 int /*<<< orphan*/  IFBF_FLUSHDYN ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bridge_rtflush (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bridge_stop(struct ifnet *ifp, int disable)
{
	struct bridge_softc *sc = ifp->if_softc;

	BRIDGE_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	callout_stop(&sc->sc_brcallout);
	bstp_stop(&sc->sc_stp);

	bridge_rtflush(sc, IFBF_FLUSHDYN);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
}