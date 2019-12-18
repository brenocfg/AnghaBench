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
struct gem_softc {int /*<<< orphan*/  sc_pdmatag; int /*<<< orphan*/  sc_rdmatag; int /*<<< orphan*/  sc_tdmatag; int /*<<< orphan*/  sc_cdmatag; int /*<<< orphan*/  sc_cddmamap; int /*<<< orphan*/  sc_control_data; TYPE_2__* sc_txsoft; TYPE_1__* sc_rxsoft; int /*<<< orphan*/  sc_miibus; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_rx_ch; int /*<<< orphan*/  sc_tick_ch; struct ifnet* sc_ifp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * txs_dmamap; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rxs_dmamap; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  GEM_CDSYNC (struct gem_softc*,int) ; 
 int /*<<< orphan*/  GEM_LOCK (struct gem_softc*) ; 
 int GEM_NRXDESC ; 
 int GEM_TXQUEUELEN ; 
 int /*<<< orphan*/  GEM_UNLOCK (struct gem_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  gem_stop (struct ifnet*,int) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 

void
gem_detach(struct gem_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	int i;

	ether_ifdetach(ifp);
	GEM_LOCK(sc);
	gem_stop(ifp, 1);
	GEM_UNLOCK(sc);
	callout_drain(&sc->sc_tick_ch);
#ifdef GEM_RINT_TIMEOUT
	callout_drain(&sc->sc_rx_ch);
#endif
	if_free(ifp);
	device_delete_child(sc->sc_dev, sc->sc_miibus);

	for (i = 0; i < GEM_NRXDESC; i++)
		if (sc->sc_rxsoft[i].rxs_dmamap != NULL)
			bus_dmamap_destroy(sc->sc_rdmatag,
			    sc->sc_rxsoft[i].rxs_dmamap);
	for (i = 0; i < GEM_TXQUEUELEN; i++)
		if (sc->sc_txsoft[i].txs_dmamap != NULL)
			bus_dmamap_destroy(sc->sc_tdmatag,
			    sc->sc_txsoft[i].txs_dmamap);
	GEM_CDSYNC(sc, BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(sc->sc_cdmatag, sc->sc_cddmamap);
	bus_dmamem_free(sc->sc_cdmatag, sc->sc_control_data,
	    sc->sc_cddmamap);
	bus_dma_tag_destroy(sc->sc_cdmatag);
	bus_dma_tag_destroy(sc->sc_tdmatag);
	bus_dma_tag_destroy(sc->sc_rdmatag);
	bus_dma_tag_destroy(sc->sc_pdmatag);
}