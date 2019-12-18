#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int rl_tx_desc_cnt; int rl_rx_desc_cnt; scalar_t__ rl_stag; int /*<<< orphan*/  rl_smap; scalar_t__ rl_stats; scalar_t__ rl_stats_addr; scalar_t__ rl_jrx_mtag; scalar_t__ rl_jrx_sparemap; TYPE_2__* rl_jrx_desc; scalar_t__ rl_rx_mtag; scalar_t__ rl_rx_sparemap; TYPE_1__* rl_rx_desc; scalar_t__ rl_tx_mtag; TYPE_3__* rl_tx_desc; scalar_t__ rl_tx_list_tag; int /*<<< orphan*/  rl_tx_list_map; scalar_t__ rl_tx_list; scalar_t__ rl_tx_list_addr; scalar_t__ rl_rx_list_tag; int /*<<< orphan*/  rl_rx_list_map; scalar_t__ rl_rx_list; scalar_t__ rl_rx_list_addr; } ;
struct rl_softc {int suspended; int rl_flags; int rl_res_id; int /*<<< orphan*/  rl_mtx; scalar_t__ rl_parent_tag; TYPE_4__ rl_ldata; int /*<<< orphan*/ * rl_res; int /*<<< orphan*/  rl_res_type; int /*<<< orphan*/ * rl_res_pba; int /*<<< orphan*/ ** rl_irq; int /*<<< orphan*/ ** rl_intrhand; scalar_t__ rl_miibus; int /*<<< orphan*/  rl_inttask; int /*<<< orphan*/  rl_stat_callout; struct ifnet* rl_ifp; } ;
struct ifnet {int if_capenable; int /*<<< orphan*/  if_flags; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {scalar_t__ tx_dmamap; } ;
struct TYPE_6__ {scalar_t__ rx_dmamap; } ;
struct TYPE_5__ {scalar_t__ rx_dmamap; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int PCIR_BAR (int) ; 
 int RL_FLAG_MSI ; 
 int RL_FLAG_MSIX ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netmap_detach (struct ifnet*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_stop (struct rl_softc*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_fast ; 

__attribute__((used)) static int
re_detach(device_t dev)
{
	struct rl_softc		*sc;
	struct ifnet		*ifp;
	int			i, rid;

	sc = device_get_softc(dev);
	ifp = sc->rl_ifp;
	KASSERT(mtx_initialized(&sc->rl_mtx), ("re mutex not initialized"));

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
#ifdef DEVICE_POLLING
		if (ifp->if_capenable & IFCAP_POLLING)
			ether_poll_deregister(ifp);
#endif
		RL_LOCK(sc);
#if 0
		sc->suspended = 1;
#endif
		re_stop(sc);
		RL_UNLOCK(sc);
		callout_drain(&sc->rl_stat_callout);
		taskqueue_drain(taskqueue_fast, &sc->rl_inttask);
		/*
		 * Force off the IFF_UP flag here, in case someone
		 * still had a BPF descriptor attached to this
		 * interface. If they do, ether_ifdetach() will cause
		 * the BPF code to try and clear the promisc mode
		 * flag, which will bubble down to re_ioctl(),
		 * which will try to call re_init() again. This will
		 * turn the NIC back on and restart the MII ticker,
		 * which will panic the system when the kernel tries
		 * to invoke the re_tick() function that isn't there
		 * anymore.
		 */
		ifp->if_flags &= ~IFF_UP;
		ether_ifdetach(ifp);
	}
	if (sc->rl_miibus)
		device_delete_child(dev, sc->rl_miibus);
	bus_generic_detach(dev);

	/*
	 * The rest is resource deallocation, so we should already be
	 * stopped here.
	 */

	if (sc->rl_intrhand[0] != NULL) {
		bus_teardown_intr(dev, sc->rl_irq[0], sc->rl_intrhand[0]);
		sc->rl_intrhand[0] = NULL;
	}
	if (ifp != NULL) {
#ifdef DEV_NETMAP
		netmap_detach(ifp);
#endif /* DEV_NETMAP */
		if_free(ifp);
	}
	if ((sc->rl_flags & (RL_FLAG_MSI | RL_FLAG_MSIX)) == 0)
		rid = 0;
	else
		rid = 1;
	if (sc->rl_irq[0] != NULL) {
		bus_release_resource(dev, SYS_RES_IRQ, rid, sc->rl_irq[0]);
		sc->rl_irq[0] = NULL;
	}
	if ((sc->rl_flags & (RL_FLAG_MSI | RL_FLAG_MSIX)) != 0)
		pci_release_msi(dev);
	if (sc->rl_res_pba) {
		rid = PCIR_BAR(4);
		bus_release_resource(dev, SYS_RES_MEMORY, rid, sc->rl_res_pba);
	}
	if (sc->rl_res)
		bus_release_resource(dev, sc->rl_res_type, sc->rl_res_id,
		    sc->rl_res);

	/* Unload and free the RX DMA ring memory and map */

	if (sc->rl_ldata.rl_rx_list_tag) {
		if (sc->rl_ldata.rl_rx_list_addr)
			bus_dmamap_unload(sc->rl_ldata.rl_rx_list_tag,
			    sc->rl_ldata.rl_rx_list_map);
		if (sc->rl_ldata.rl_rx_list)
			bus_dmamem_free(sc->rl_ldata.rl_rx_list_tag,
			    sc->rl_ldata.rl_rx_list,
			    sc->rl_ldata.rl_rx_list_map);
		bus_dma_tag_destroy(sc->rl_ldata.rl_rx_list_tag);
	}

	/* Unload and free the TX DMA ring memory and map */

	if (sc->rl_ldata.rl_tx_list_tag) {
		if (sc->rl_ldata.rl_tx_list_addr)
			bus_dmamap_unload(sc->rl_ldata.rl_tx_list_tag,
			    sc->rl_ldata.rl_tx_list_map);
		if (sc->rl_ldata.rl_tx_list)
			bus_dmamem_free(sc->rl_ldata.rl_tx_list_tag,
			    sc->rl_ldata.rl_tx_list,
			    sc->rl_ldata.rl_tx_list_map);
		bus_dma_tag_destroy(sc->rl_ldata.rl_tx_list_tag);
	}

	/* Destroy all the RX and TX buffer maps */

	if (sc->rl_ldata.rl_tx_mtag) {
		for (i = 0; i < sc->rl_ldata.rl_tx_desc_cnt; i++) {
			if (sc->rl_ldata.rl_tx_desc[i].tx_dmamap)
				bus_dmamap_destroy(sc->rl_ldata.rl_tx_mtag,
				    sc->rl_ldata.rl_tx_desc[i].tx_dmamap);
		}
		bus_dma_tag_destroy(sc->rl_ldata.rl_tx_mtag);
	}
	if (sc->rl_ldata.rl_rx_mtag) {
		for (i = 0; i < sc->rl_ldata.rl_rx_desc_cnt; i++) {
			if (sc->rl_ldata.rl_rx_desc[i].rx_dmamap)
				bus_dmamap_destroy(sc->rl_ldata.rl_rx_mtag,
				    sc->rl_ldata.rl_rx_desc[i].rx_dmamap);
		}
		if (sc->rl_ldata.rl_rx_sparemap)
			bus_dmamap_destroy(sc->rl_ldata.rl_rx_mtag,
			    sc->rl_ldata.rl_rx_sparemap);
		bus_dma_tag_destroy(sc->rl_ldata.rl_rx_mtag);
	}
	if (sc->rl_ldata.rl_jrx_mtag) {
		for (i = 0; i < sc->rl_ldata.rl_rx_desc_cnt; i++) {
			if (sc->rl_ldata.rl_jrx_desc[i].rx_dmamap)
				bus_dmamap_destroy(sc->rl_ldata.rl_jrx_mtag,
				    sc->rl_ldata.rl_jrx_desc[i].rx_dmamap);
		}
		if (sc->rl_ldata.rl_jrx_sparemap)
			bus_dmamap_destroy(sc->rl_ldata.rl_jrx_mtag,
			    sc->rl_ldata.rl_jrx_sparemap);
		bus_dma_tag_destroy(sc->rl_ldata.rl_jrx_mtag);
	}
	/* Unload and free the stats buffer and map */

	if (sc->rl_ldata.rl_stag) {
		if (sc->rl_ldata.rl_stats_addr)
			bus_dmamap_unload(sc->rl_ldata.rl_stag,
			    sc->rl_ldata.rl_smap);
		if (sc->rl_ldata.rl_stats)
			bus_dmamem_free(sc->rl_ldata.rl_stag,
			    sc->rl_ldata.rl_stats, sc->rl_ldata.rl_smap);
		bus_dma_tag_destroy(sc->rl_ldata.rl_stag);
	}

	if (sc->rl_parent_tag)
		bus_dma_tag_destroy(sc->rl_parent_tag);

	mtx_destroy(&sc->rl_mtx);

	return (0);
}