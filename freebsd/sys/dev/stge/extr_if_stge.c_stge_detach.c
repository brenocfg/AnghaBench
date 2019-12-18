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
struct stge_softc {int sc_detach; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_mii_mtx; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_spec; int /*<<< orphan*/ * sc_ih; struct ifnet* sc_ifp; int /*<<< orphan*/ * sc_miibus; int /*<<< orphan*/  sc_link_task; int /*<<< orphan*/  sc_tick_ch; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct stge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stge_dma_free (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_stop (struct stge_softc*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static int
stge_detach(device_t dev)
{
	struct stge_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	ifp = sc->sc_ifp;
#ifdef DEVICE_POLLING
	if (ifp && ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif
	if (device_is_attached(dev)) {
		STGE_LOCK(sc);
		/* XXX */
		sc->sc_detach = 1;
		stge_stop(sc);
		STGE_UNLOCK(sc);
		callout_drain(&sc->sc_tick_ch);
		taskqueue_drain(taskqueue_swi, &sc->sc_link_task);
		ether_ifdetach(ifp);
	}

	if (sc->sc_miibus != NULL) {
		device_delete_child(dev, sc->sc_miibus);
		sc->sc_miibus = NULL;
	}
	bus_generic_detach(dev);
	stge_dma_free(sc);

	if (ifp != NULL) {
		if_free(ifp);
		sc->sc_ifp = NULL;
	}

	if (sc->sc_ih) {
		bus_teardown_intr(dev, sc->sc_res[1], sc->sc_ih);
		sc->sc_ih = NULL;
	}
	bus_release_resources(dev, sc->sc_spec, sc->sc_res);

	mtx_destroy(&sc->sc_mii_mtx);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}