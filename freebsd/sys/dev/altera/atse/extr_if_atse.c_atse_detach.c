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
struct atse_softc {int /*<<< orphan*/  xdma_rx; int /*<<< orphan*/  xdma_tx; int /*<<< orphan*/  xchan_rx; int /*<<< orphan*/  xchan_tx; int /*<<< orphan*/  atse_mtx; int /*<<< orphan*/ * atse_miibus; int /*<<< orphan*/  atse_tick; struct ifnet* atse_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATSE_LOCK (struct atse_softc*) ; 
 int /*<<< orphan*/  ATSE_UNLOCK (struct atse_softc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atse_stop_locked (struct atse_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct atse_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdma_channel_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdma_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atse_detach(device_t dev)
{
	struct atse_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->atse_mtx), ("%s: mutex not initialized",
	    device_get_nameunit(dev)));
	ifp = sc->atse_ifp;

	/* Only cleanup if attach succeeded. */
	if (device_is_attached(dev)) {
		ATSE_LOCK(sc);
		atse_stop_locked(sc);
		ATSE_UNLOCK(sc);
		callout_drain(&sc->atse_tick);
		ether_ifdetach(ifp);
	}
	if (sc->atse_miibus != NULL) {
		device_delete_child(dev, sc->atse_miibus);
	}

	if (ifp != NULL) {
		if_free(ifp);
	}

	mtx_destroy(&sc->atse_mtx);

	xdma_channel_free(sc->xchan_tx);
	xdma_channel_free(sc->xchan_rx);
	xdma_put(sc->xdma_tx);
	xdma_put(sc->xdma_rx);

	return (0);
}