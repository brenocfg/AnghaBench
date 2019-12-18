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
struct vte_softc {struct ifnet* vte_ifp; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  VTE_LOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_UNLOCK (struct vte_softc*) ; 
 struct vte_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vte_init_locked (struct vte_softc*) ; 

__attribute__((used)) static int
vte_resume(device_t dev)
{
	struct vte_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	VTE_LOCK(sc);
	ifp = sc->vte_ifp;
	if ((ifp->if_flags & IFF_UP) != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		vte_init_locked(sc);
	}
	VTE_UNLOCK(sc);

	return (0);
}