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
struct xae_softc {int /*<<< orphan*/  xdma_rx; int /*<<< orphan*/  xdma_tx; int /*<<< orphan*/  xchan_rx; int /*<<< orphan*/  xchan_tx; int /*<<< orphan*/ * res; int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * miibus; int /*<<< orphan*/  xae_callout; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XAE_LOCK (struct xae_softc*) ; 
 int /*<<< orphan*/  XAE_UNLOCK (struct xae_softc*) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct xae_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xae_spec ; 
 int /*<<< orphan*/  xae_stop_locked (struct xae_softc*) ; 
 int /*<<< orphan*/  xdma_channel_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdma_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xae_detach(device_t dev)
{
	struct xae_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	KASSERT(mtx_initialized(&sc->mtx), ("%s: mutex not initialized",
	    device_get_nameunit(dev)));

	ifp = sc->ifp;

	/* Only cleanup if attach succeeded. */
	if (device_is_attached(dev)) {
		XAE_LOCK(sc);
		xae_stop_locked(sc);
		XAE_UNLOCK(sc);
		callout_drain(&sc->xae_callout);
		ether_ifdetach(ifp);
	}

	if (sc->miibus != NULL)
		device_delete_child(dev, sc->miibus);

	if (ifp != NULL)
		if_free(ifp);

	mtx_destroy(&sc->mtx);

	bus_teardown_intr(dev, sc->res[1], sc->intr_cookie);

	bus_release_resources(dev, xae_spec, sc->res);

	xdma_channel_free(sc->xchan_tx);
	xdma_channel_free(sc->xchan_rx);
	xdma_put(sc->xdma_tx);
	xdma_put(sc->xdma_rx);

	return (0);
}