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
struct ifnet {int if_flags; int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct bfe_softc {struct ifnet* bfe_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_LOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  BFE_UNLOCK (struct bfe_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfe_chip_reset (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_init_locked (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_start_locked (struct ifnet*) ; 
 struct bfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bfe_resume(device_t dev)
{
	struct bfe_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	ifp = sc->bfe_ifp;
	BFE_LOCK(sc);
	bfe_chip_reset(sc);
	if (ifp->if_flags & IFF_UP) {
		bfe_init_locked(sc);
		if (ifp->if_drv_flags & IFF_DRV_RUNNING &&
		    !IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			bfe_start_locked(ifp);
	}
	BFE_UNLOCK(sc);

	return (0);
}