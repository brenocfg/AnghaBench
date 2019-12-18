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
struct nge_softc {int /*<<< orphan*/ * nge_res; int /*<<< orphan*/  nge_res_id; int /*<<< orphan*/  nge_res_type; int /*<<< orphan*/ * nge_irq; int /*<<< orphan*/ * nge_intrhand; int /*<<< orphan*/ * nge_miibus; int /*<<< orphan*/  nge_stat_ch; int /*<<< orphan*/  nge_flags; struct ifnet* nge_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  NGE_FLAG_DETACH ; 
 int /*<<< orphan*/  NGE_LOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_LOCK_DESTROY (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_UNLOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  nge_dma_free (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_stop (struct nge_softc*) ; 

__attribute__((used)) static int
nge_detach(device_t dev)
{
	struct nge_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	ifp = sc->nge_ifp;

#ifdef DEVICE_POLLING
	if (ifp != NULL && ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	if (device_is_attached(dev)) {
		NGE_LOCK(sc);
		sc->nge_flags |= NGE_FLAG_DETACH;
		nge_stop(sc);
		NGE_UNLOCK(sc);
		callout_drain(&sc->nge_stat_ch);
		if (ifp != NULL)
			ether_ifdetach(ifp);
	}

	if (sc->nge_miibus != NULL) {
		device_delete_child(dev, sc->nge_miibus);
		sc->nge_miibus = NULL;
	}
	bus_generic_detach(dev);
	if (sc->nge_intrhand != NULL)
		bus_teardown_intr(dev, sc->nge_irq, sc->nge_intrhand);
	if (sc->nge_irq != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->nge_irq);
	if (sc->nge_res != NULL)
		bus_release_resource(dev, sc->nge_res_type, sc->nge_res_id,
		    sc->nge_res);

	nge_dma_free(sc);
	if (ifp != NULL)
		if_free(ifp);

	NGE_LOCK_DESTROY(sc);

	return (0);
}