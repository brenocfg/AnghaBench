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
typedef  int /*<<< orphan*/  uint8_t ;
struct nfe_softc {int nfe_flags; scalar_t__ nfe_msi; scalar_t__ nfe_msix; int /*<<< orphan*/  nfe_mtx; int /*<<< orphan*/ * nfe_parent_tag; int /*<<< orphan*/  jrxq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  txq; int /*<<< orphan*/ ** nfe_res; int /*<<< orphan*/ * nfe_msix_res; int /*<<< orphan*/ * nfe_msix_pba_res; int /*<<< orphan*/ ** nfe_irq; int /*<<< orphan*/ ** nfe_intrhand; int /*<<< orphan*/ * nfe_tq; int /*<<< orphan*/  nfe_int_task; scalar_t__ nfe_miibus; int /*<<< orphan*/ * eaddr; int /*<<< orphan*/  nfe_stat_ch; int /*<<< orphan*/ * nfe_ifp; } ;
typedef  int /*<<< orphan*/ * if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int NFE_CORRECT_MACADDR ; 
 int /*<<< orphan*/  NFE_LOCK (struct nfe_softc*) ; 
 int NFE_MSI_MESSAGES ; 
 int /*<<< orphan*/  NFE_UNLOCK (struct nfe_softc*) ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct nfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_poll_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int if_getcapenable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_setflagbits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfe_free_jrx_ring (struct nfe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfe_free_rx_ring (struct nfe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfe_free_tx_ring (struct nfe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfe_set_macaddr (struct nfe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfe_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfe_detach(device_t dev)
{
	struct nfe_softc *sc;
	if_t ifp;
	uint8_t eaddr[ETHER_ADDR_LEN];
	int i, rid;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->nfe_mtx), ("nfe mutex not initialized"));
	ifp = sc->nfe_ifp;

#ifdef DEVICE_POLLING
	if (ifp != NULL && if_getcapenable(ifp) & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif
	if (device_is_attached(dev)) {
		NFE_LOCK(sc);
		nfe_stop(ifp);
		if_setflagbits(ifp, 0, IFF_UP);
		NFE_UNLOCK(sc);
		callout_drain(&sc->nfe_stat_ch);
		ether_ifdetach(ifp);
	}

	if (ifp) {
		/* restore ethernet address */
		if ((sc->nfe_flags & NFE_CORRECT_MACADDR) == 0) {
			for (i = 0; i < ETHER_ADDR_LEN; i++) {
				eaddr[i] = sc->eaddr[5 - i];
			}
		} else
			bcopy(sc->eaddr, eaddr, ETHER_ADDR_LEN);
		nfe_set_macaddr(sc, eaddr);
		if_free(ifp);
	}
	if (sc->nfe_miibus)
		device_delete_child(dev, sc->nfe_miibus);
	bus_generic_detach(dev);
	if (sc->nfe_tq != NULL) {
		taskqueue_drain(sc->nfe_tq, &sc->nfe_int_task);
		taskqueue_free(sc->nfe_tq);
		sc->nfe_tq = NULL;
	}

	for (i = 0; i < NFE_MSI_MESSAGES; i++) {
		if (sc->nfe_intrhand[i] != NULL) {
			bus_teardown_intr(dev, sc->nfe_irq[i],
			    sc->nfe_intrhand[i]);
			sc->nfe_intrhand[i] = NULL;
		}
	}

	if (sc->nfe_msi == 0 && sc->nfe_msix == 0) {
		if (sc->nfe_irq[0] != NULL)
			bus_release_resource(dev, SYS_RES_IRQ, 0,
			    sc->nfe_irq[0]);
	} else {
		for (i = 0, rid = 1; i < NFE_MSI_MESSAGES; i++, rid++) {
			if (sc->nfe_irq[i] != NULL) {
				bus_release_resource(dev, SYS_RES_IRQ, rid,
				    sc->nfe_irq[i]);
				sc->nfe_irq[i] = NULL;
			}
		}
		pci_release_msi(dev);
	}
	if (sc->nfe_msix_pba_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BAR(3),
		    sc->nfe_msix_pba_res);
		sc->nfe_msix_pba_res = NULL;
	}
	if (sc->nfe_msix_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BAR(2),
		    sc->nfe_msix_res);
		sc->nfe_msix_res = NULL;
	}
	if (sc->nfe_res[0] != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BAR(0),
		    sc->nfe_res[0]);
		sc->nfe_res[0] = NULL;
	}

	nfe_free_tx_ring(sc, &sc->txq);
	nfe_free_rx_ring(sc, &sc->rxq);
	nfe_free_jrx_ring(sc, &sc->jrxq);

	if (sc->nfe_parent_tag) {
		bus_dma_tag_destroy(sc->nfe_parent_tag);
		sc->nfe_parent_tag = NULL;
	}

	mtx_destroy(&sc->nfe_mtx);

	return (0);
}