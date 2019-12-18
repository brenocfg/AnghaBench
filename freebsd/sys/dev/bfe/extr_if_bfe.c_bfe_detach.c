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
struct ifnet {int dummy; } ;
struct bfe_softc {int /*<<< orphan*/  bfe_mtx; int /*<<< orphan*/ * bfe_miibus; int /*<<< orphan*/  bfe_stat_co; int /*<<< orphan*/  bfe_flags; struct ifnet* bfe_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_FLAG_DETACH ; 
 int /*<<< orphan*/  BFE_LOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  BFE_UNLOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_chip_reset (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_dma_free (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_release_resources (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_stop (struct bfe_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bfe_detach(device_t dev)
{
	struct bfe_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	ifp = sc->bfe_ifp;

	if (device_is_attached(dev)) {
		BFE_LOCK(sc);
		sc->bfe_flags |= BFE_FLAG_DETACH;
		bfe_stop(sc);
		BFE_UNLOCK(sc);
		callout_drain(&sc->bfe_stat_co);
		if (ifp != NULL)
			ether_ifdetach(ifp);
	}

	BFE_LOCK(sc);
	bfe_chip_reset(sc);
	BFE_UNLOCK(sc);

	bus_generic_detach(dev);
	if (sc->bfe_miibus != NULL)
		device_delete_child(dev, sc->bfe_miibus);

	bfe_release_resources(sc);
	bfe_dma_free(sc);
	mtx_destroy(&sc->bfe_mtx);

	return (0);
}