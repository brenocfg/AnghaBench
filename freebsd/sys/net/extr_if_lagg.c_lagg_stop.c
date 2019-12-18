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
struct lagg_softc {struct ifnet* sc_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LAGG_XLOCK_ASSERT (struct lagg_softc*) ; 
 int /*<<< orphan*/  lagg_proto_stop (struct lagg_softc*) ; 

__attribute__((used)) static void
lagg_stop(struct lagg_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	LAGG_XLOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;

	lagg_proto_stop(sc);
}