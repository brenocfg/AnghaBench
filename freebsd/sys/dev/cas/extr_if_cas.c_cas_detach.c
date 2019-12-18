#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
struct cas_softc {int /*<<< orphan*/  sc_pdmatag; int /*<<< orphan*/  sc_rdmatag; int /*<<< orphan*/  sc_tdmatag; int /*<<< orphan*/  sc_cdmatag; int /*<<< orphan*/ * sc_cddmamap; int /*<<< orphan*/ * sc_control_data; TYPE_2__* sc_txsoft; TYPE_1__* sc_rxdsoft; int /*<<< orphan*/  sc_miibus; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/  sc_tx_task; int /*<<< orphan*/  sc_intr_task; int /*<<< orphan*/  sc_rx_ch; int /*<<< orphan*/  sc_tick_ch; struct ifnet* sc_ifp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * txs_dmamap; } ;
struct TYPE_3__ {scalar_t__ rxds_paddr; int /*<<< orphan*/ * rxds_dmamap; int /*<<< orphan*/ * rxds_buf; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CAS_CDSYNC (struct cas_softc*,int) ; 
 int /*<<< orphan*/  CAS_LOCK (struct cas_softc*) ; 
 int CAS_NRXDESC ; 
 int CAS_TXQUEUELEN ; 
 int /*<<< orphan*/  CAS_UNLOCK (struct cas_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cas_stop (struct ifnet*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cas_detach(struct cas_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	int i;

	ether_ifdetach(ifp);
	CAS_LOCK(sc);
	cas_stop(ifp);
	CAS_UNLOCK(sc);
	callout_drain(&sc->sc_tick_ch);
	callout_drain(&sc->sc_rx_ch);
	taskqueue_drain(sc->sc_tq, &sc->sc_intr_task);
	taskqueue_drain(sc->sc_tq, &sc->sc_tx_task);
	if_free(ifp);
	taskqueue_free(sc->sc_tq);
	device_delete_child(sc->sc_dev, sc->sc_miibus);

	for (i = 0; i < CAS_NRXDESC; i++)
		if (sc->sc_rxdsoft[i].rxds_dmamap != NULL)
			bus_dmamap_sync(sc->sc_rdmatag,
			    sc->sc_rxdsoft[i].rxds_dmamap,
			    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	for (i = 0; i < CAS_NRXDESC; i++)
		if (sc->sc_rxdsoft[i].rxds_paddr != 0)
			bus_dmamap_unload(sc->sc_rdmatag,
			    sc->sc_rxdsoft[i].rxds_dmamap);
	for (i = 0; i < CAS_NRXDESC; i++)
		if (sc->sc_rxdsoft[i].rxds_buf != NULL)
			bus_dmamem_free(sc->sc_rdmatag,
			    sc->sc_rxdsoft[i].rxds_buf,
			    sc->sc_rxdsoft[i].rxds_dmamap);
	for (i = 0; i < CAS_TXQUEUELEN; i++)
		if (sc->sc_txsoft[i].txs_dmamap != NULL)
			bus_dmamap_destroy(sc->sc_tdmatag,
			    sc->sc_txsoft[i].txs_dmamap);
	CAS_CDSYNC(sc, BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(sc->sc_cdmatag, sc->sc_cddmamap);
	bus_dmamem_free(sc->sc_cdmatag, sc->sc_control_data,
	    sc->sc_cddmamap);
	bus_dma_tag_destroy(sc->sc_cdmatag);
	bus_dma_tag_destroy(sc->sc_tdmatag);
	bus_dma_tag_destroy(sc->sc_rdmatag);
	bus_dma_tag_destroy(sc->sc_pdmatag);
}