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
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
struct emac_softc {struct ifnet* emac_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_LOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  EMAC_UNLOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 struct emac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_init_locked (struct emac_softc*) ; 

__attribute__((used)) static int
emac_resume(device_t dev)
{
	struct emac_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	EMAC_LOCK(sc);
	ifp = sc->emac_ifp;
	if ((ifp->if_flags & IFF_UP) != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		emac_init_locked(sc);
	}
	EMAC_UNLOCK(sc);

	return (0);
}