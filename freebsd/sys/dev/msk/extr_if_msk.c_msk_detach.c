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
struct msk_softc {int /*<<< orphan*/ ** msk_if; int /*<<< orphan*/  msk_mtx; } ;
struct msk_if_softc {size_t msk_port; struct msk_softc* msk_softc; int /*<<< orphan*/  msk_tick_ch; int /*<<< orphan*/  msk_flags; struct ifnet* msk_ifp; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MSK_FLAG_DETACH ; 
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct msk_if_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  msk_rx_dma_jfree (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_stop (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_txrx_dma_free (struct msk_if_softc*) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
msk_detach(device_t dev)
{
	struct msk_softc *sc;
	struct msk_if_softc *sc_if;
	struct ifnet *ifp;

	sc_if = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc_if->msk_softc->msk_mtx),
	    ("msk mutex not initialized in msk_detach"));
	MSK_IF_LOCK(sc_if);

	ifp = sc_if->msk_ifp;
	if (device_is_attached(dev)) {
		/* XXX */
		sc_if->msk_flags |= MSK_FLAG_DETACH;
		msk_stop(sc_if);
		/* Can't hold locks while calling detach. */
		MSK_IF_UNLOCK(sc_if);
		callout_drain(&sc_if->msk_tick_ch);
		if (ifp)
			ether_ifdetach(ifp);
		MSK_IF_LOCK(sc_if);
	}

	/*
	 * We're generally called from mskc_detach() which is using
	 * device_delete_child() to get to here. It's already trashed
	 * miibus for us, so don't do it here or we'll panic.
	 *
	 * if (sc_if->msk_miibus != NULL) {
	 * 	device_delete_child(dev, sc_if->msk_miibus);
	 * 	sc_if->msk_miibus = NULL;
	 * }
	 */

	msk_rx_dma_jfree(sc_if);
	msk_txrx_dma_free(sc_if);
	bus_generic_detach(dev);

	sc = sc_if->msk_softc;
	sc->msk_if[sc_if->msk_port] = NULL;
	MSK_IF_UNLOCK(sc_if);
	if (ifp)
		if_free(ifp);

	return (0);
}