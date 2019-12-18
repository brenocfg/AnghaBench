#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ xl_tx_tag; int /*<<< orphan*/  xl_tx_dmamap; int /*<<< orphan*/  xl_tx_list; scalar_t__ xl_rx_tag; int /*<<< orphan*/  xl_rx_dmamap; int /*<<< orphan*/  xl_rx_list; } ;
struct xl_softc {int xl_flags; int /*<<< orphan*/  xl_mtx; TYPE_1__ xl_ldata; scalar_t__ xl_mtag; int /*<<< orphan*/  xl_tmpmap; int /*<<< orphan*/ * xl_res; int /*<<< orphan*/ * xl_fres; int /*<<< orphan*/ * xl_irq; scalar_t__ xl_intrhand; int /*<<< orphan*/  ifmedia; scalar_t__ xl_miibus; int /*<<< orphan*/  xl_tick_callout; int /*<<< orphan*/  xl_task; struct ifnet* xl_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int XL_FLAG_USE_MMIO ; 
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 int XL_PCI_FUNCMEM ; 
 int XL_PCI_LOIO ; 
 int XL_PCI_LOMEM ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct xl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 
 int /*<<< orphan*/  xl_stop (struct xl_softc*) ; 

__attribute__((used)) static int
xl_detach(device_t dev)
{
	struct xl_softc		*sc;
	struct ifnet		*ifp;
	int			rid, res;

	sc = device_get_softc(dev);
	ifp = sc->xl_ifp;

	KASSERT(mtx_initialized(&sc->xl_mtx), ("xl mutex not initialized"));

#ifdef DEVICE_POLLING
	if (ifp && ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	if (sc->xl_flags & XL_FLAG_USE_MMIO) {
		rid = XL_PCI_LOMEM;
		res = SYS_RES_MEMORY;
	} else {
		rid = XL_PCI_LOIO;
		res = SYS_RES_IOPORT;
	}

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		XL_LOCK(sc);
		xl_stop(sc);
		XL_UNLOCK(sc);
		taskqueue_drain(taskqueue_swi, &sc->xl_task);
		callout_drain(&sc->xl_tick_callout);
		ether_ifdetach(ifp);
	}
	if (sc->xl_miibus)
		device_delete_child(dev, sc->xl_miibus);
	bus_generic_detach(dev);
	ifmedia_removeall(&sc->ifmedia);

	if (sc->xl_intrhand)
		bus_teardown_intr(dev, sc->xl_irq, sc->xl_intrhand);
	if (sc->xl_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->xl_irq);
	if (sc->xl_fres != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    XL_PCI_FUNCMEM, sc->xl_fres);
	if (sc->xl_res)
		bus_release_resource(dev, res, rid, sc->xl_res);

	if (ifp)
		if_free(ifp);

	if (sc->xl_mtag) {
		bus_dmamap_destroy(sc->xl_mtag, sc->xl_tmpmap);
		bus_dma_tag_destroy(sc->xl_mtag);
	}
	if (sc->xl_ldata.xl_rx_tag) {
		bus_dmamap_unload(sc->xl_ldata.xl_rx_tag,
		    sc->xl_ldata.xl_rx_dmamap);
		bus_dmamem_free(sc->xl_ldata.xl_rx_tag, sc->xl_ldata.xl_rx_list,
		    sc->xl_ldata.xl_rx_dmamap);
		bus_dma_tag_destroy(sc->xl_ldata.xl_rx_tag);
	}
	if (sc->xl_ldata.xl_tx_tag) {
		bus_dmamap_unload(sc->xl_ldata.xl_tx_tag,
		    sc->xl_ldata.xl_tx_dmamap);
		bus_dmamem_free(sc->xl_ldata.xl_tx_tag, sc->xl_ldata.xl_tx_list,
		    sc->xl_ldata.xl_tx_dmamap);
		bus_dma_tag_destroy(sc->xl_ldata.xl_tx_tag);
	}

	mtx_destroy(&sc->xl_mtx);

	return (0);
}