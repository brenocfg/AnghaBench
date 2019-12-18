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
struct vte_txdesc {int tx_flags; int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** vte_txmbufs; int /*<<< orphan*/  vte_tx_tag; struct vte_txdesc* vte_txdesc; int /*<<< orphan*/  vte_rx_tag; struct vte_rxdesc* vte_rxdesc; } ;
struct vte_softc {TYPE_1__ vte_cdata; scalar_t__ vte_watchdog_timer; int /*<<< orphan*/  vte_tick_ch; int /*<<< orphan*/  vte_flags; struct ifnet* vte_ifp; } ;
struct vte_rxdesc {int /*<<< orphan*/ * rx_m; int /*<<< orphan*/  rx_dmamap; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CSR_READ_2 (struct vte_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vte_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  VTE_FLAG_LINK ; 
 int /*<<< orphan*/  VTE_LOCK_ASSERT (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_MECIER ; 
 int /*<<< orphan*/  VTE_MIER ; 
 int /*<<< orphan*/  VTE_MISR ; 
 int VTE_RX_RING_CNT ; 
 int VTE_TXMBUF ; 
 int VTE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vte_stats_update (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_stop_mac (struct vte_softc*) ; 

__attribute__((used)) static void
vte_stop(struct vte_softc *sc)
{
	struct ifnet *ifp;
	struct vte_txdesc *txd;
	struct vte_rxdesc *rxd;
	int i;

	VTE_LOCK_ASSERT(sc);
	/*
	 * Mark the interface down and cancel the watchdog timer.
	 */
	ifp = sc->vte_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->vte_flags &= ~VTE_FLAG_LINK;
	callout_stop(&sc->vte_tick_ch);
	sc->vte_watchdog_timer = 0;
	vte_stats_update(sc);
	/* Disable interrupts. */
	CSR_WRITE_2(sc, VTE_MIER, 0);
	CSR_WRITE_2(sc, VTE_MECIER, 0);
	/* Stop RX/TX MACs. */
	vte_stop_mac(sc);
	/* Clear interrupts. */
	CSR_READ_2(sc, VTE_MISR);
	/*
	 * Free TX/RX mbufs still in the queues.
	 */
	for (i = 0; i < VTE_RX_RING_CNT; i++) {
		rxd = &sc->vte_cdata.vte_rxdesc[i];
		if (rxd->rx_m != NULL) {
			bus_dmamap_sync(sc->vte_cdata.vte_rx_tag,
			    rxd->rx_dmamap, BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->vte_cdata.vte_rx_tag,
			    rxd->rx_dmamap);
			m_freem(rxd->rx_m);
			rxd->rx_m = NULL;
		}
	}
	for (i = 0; i < VTE_TX_RING_CNT; i++) {
		txd = &sc->vte_cdata.vte_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->vte_cdata.vte_tx_tag,
			    txd->tx_dmamap, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->vte_cdata.vte_tx_tag,
			    txd->tx_dmamap);
			if ((txd->tx_flags & VTE_TXMBUF) == 0)
				m_freem(txd->tx_m);
			txd->tx_m = NULL;
			txd->tx_flags &= ~VTE_TXMBUF;
		}
	}
	/* Free TX mbuf pools used for deep copy. */
	for (i = 0; i < VTE_TX_RING_CNT; i++) {
		if (sc->vte_cdata.vte_txmbufs[i] != NULL) {
			m_freem(sc->vte_cdata.vte_txmbufs[i]);
			sc->vte_cdata.vte_txmbufs[i] = NULL;
		}
	}
}