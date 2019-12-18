#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rb_membase; TYPE_2__* rb_rxdesc; int /*<<< orphan*/  rb_spare_dmamap; TYPE_1__* rb_txdesc; } ;
struct hme_softc {int /*<<< orphan*/  sc_pdmatag; int /*<<< orphan*/  sc_cdmatag; int /*<<< orphan*/  sc_rdmatag; int /*<<< orphan*/  sc_tdmatag; int /*<<< orphan*/  sc_cdmamap; TYPE_3__ sc_rb; int /*<<< orphan*/  sc_miibus; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_tick_ch; struct ifnet* sc_ifp; } ;
struct TYPE_5__ {int /*<<< orphan*/  hrx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/  htx_dmamap; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  HME_LOCK (struct hme_softc*) ; 
 int HME_NRXDESC ; 
 int HME_NTXQ ; 
 int /*<<< orphan*/  HME_UNLOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  hme_stop (struct hme_softc*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 

void
hme_detach(struct hme_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	int i;

	HME_LOCK(sc);
	hme_stop(sc);
	HME_UNLOCK(sc);
	callout_drain(&sc->sc_tick_ch);
	ether_ifdetach(ifp);
	if_free(ifp);
	device_delete_child(sc->sc_dev, sc->sc_miibus);

	for (i = 0; i < HME_NTXQ; i++) {
		bus_dmamap_destroy(sc->sc_tdmatag,
		    sc->sc_rb.rb_txdesc[i].htx_dmamap);
	}
	bus_dmamap_destroy(sc->sc_rdmatag, sc->sc_rb.rb_spare_dmamap);
	for (i = 0; i < HME_NRXDESC; i++) {
		bus_dmamap_destroy(sc->sc_rdmatag,
		    sc->sc_rb.rb_rxdesc[i].hrx_dmamap);
	}
	bus_dmamap_sync(sc->sc_cdmatag, sc->sc_cdmamap,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(sc->sc_cdmatag, sc->sc_cdmamap);
	bus_dmamem_free(sc->sc_cdmatag, sc->sc_rb.rb_membase, sc->sc_cdmamap);
	bus_dma_tag_destroy(sc->sc_tdmatag);
	bus_dma_tag_destroy(sc->sc_rdmatag);
	bus_dma_tag_destroy(sc->sc_cdmatag);
	bus_dma_tag_destroy(sc->sc_pdmatag);
}