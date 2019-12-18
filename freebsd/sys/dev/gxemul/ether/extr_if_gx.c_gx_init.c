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
struct gx_softc {struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 

__attribute__((used)) static void
gx_init(void *arg)
{
	struct ifnet *ifp;
	struct gx_softc *sc;

	sc = arg;
	ifp = sc->sc_ifp;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
}