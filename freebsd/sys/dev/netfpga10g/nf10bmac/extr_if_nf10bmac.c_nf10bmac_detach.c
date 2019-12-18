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
struct nf10bmac_softc {int /*<<< orphan*/  nf10bmac_mtx; int /*<<< orphan*/  nf10bmac_media; scalar_t__ nf10bmac_rx_intrhand; int /*<<< orphan*/  nf10bmac_rx_irq_res; int /*<<< orphan*/  nf10bmac_tick; struct ifnet* nf10bmac_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NF10BMAC_LOCK (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_UNLOCK (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct nf10bmac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf10bmac_stop_locked (struct nf10bmac_softc*) ; 

__attribute__((used)) static int
nf10bmac_detach(device_t dev)
{
	struct nf10bmac_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->nf10bmac_mtx),
	    ("%s: mutex not initialized", device_get_nameunit(dev)));
	ifp = sc->nf10bmac_ifp;

#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	/* Only cleanup if attach succeeded. */
	if (device_is_attached(dev)) {
		NF10BMAC_LOCK(sc);
		nf10bmac_stop_locked(sc);
		NF10BMAC_UNLOCK(sc);
#ifdef ENABLE_WATCHDOG
		callout_drain(&sc->nf10bmac_tick);
#endif
		ether_ifdetach(ifp);
	}

	if (sc->nf10bmac_rx_intrhand)
		bus_teardown_intr(dev, sc->nf10bmac_rx_irq_res,
		    sc->nf10bmac_rx_intrhand);

	if (ifp != NULL)
		if_free(ifp);
	ifmedia_removeall(&sc->nf10bmac_media);

	mtx_destroy(&sc->nf10bmac_mtx);

	return (0);
}