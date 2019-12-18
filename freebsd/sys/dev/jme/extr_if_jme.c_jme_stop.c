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
struct jme_txdesc {scalar_t__ tx_ndesc; int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_2__ {int /*<<< orphan*/  jme_tx_tag; struct jme_txdesc* jme_txdesc; int /*<<< orphan*/  jme_rx_tag; struct jme_rxdesc* jme_rxdesc; int /*<<< orphan*/ * jme_rxhead; } ;
struct jme_softc {TYPE_1__ jme_cdata; scalar_t__ jme_watchdog_timer; int /*<<< orphan*/  jme_tick_ch; int /*<<< orphan*/  jme_flags; struct ifnet* jme_ifp; } ;
struct jme_rxdesc {int /*<<< orphan*/ * rx_m; int /*<<< orphan*/  rx_dmamap; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  JME_FLAG_LINK ; 
 int JME_INTRS ; 
 int /*<<< orphan*/  JME_INTR_MASK_CLR ; 
 int /*<<< orphan*/  JME_INTR_STATUS ; 
 int /*<<< orphan*/  JME_LOCK_ASSERT (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_RXCHAIN_RESET (struct jme_softc*) ; 
 int JME_RX_RING_CNT ; 
 int /*<<< orphan*/  JME_SHBASE_ADDR_LO ; 
 int JME_TX_RING_CNT ; 
 int SHBASE_POST_ENB ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_rxintr (struct jme_softc*,int) ; 
 int /*<<< orphan*/  jme_stats_save (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_stats_update (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_stop_rx (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_stop_tx (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_txeof (struct jme_softc*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_stop(struct jme_softc *sc)
{
	struct ifnet *ifp;
	struct jme_txdesc *txd;
	struct jme_rxdesc *rxd;
	int i;

	JME_LOCK_ASSERT(sc);
	/*
	 * Mark the interface down and cancel the watchdog timer.
	 */
	ifp = sc->jme_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->jme_flags &= ~JME_FLAG_LINK;
	callout_stop(&sc->jme_tick_ch);
	sc->jme_watchdog_timer = 0;

	/*
	 * Disable interrupts.
	 */
	CSR_WRITE_4(sc, JME_INTR_MASK_CLR, JME_INTRS);
	CSR_WRITE_4(sc, JME_INTR_STATUS, 0xFFFFFFFF);

	/* Disable updating shadow status block. */
	CSR_WRITE_4(sc, JME_SHBASE_ADDR_LO,
	    CSR_READ_4(sc, JME_SHBASE_ADDR_LO) & ~SHBASE_POST_ENB);

	/* Stop receiver, transmitter. */
	jme_stop_rx(sc);
	jme_stop_tx(sc);

	 /* Reclaim Rx/Tx buffers that have been completed. */
	jme_rxintr(sc, JME_RX_RING_CNT);
	if (sc->jme_cdata.jme_rxhead != NULL)
		m_freem(sc->jme_cdata.jme_rxhead);
	JME_RXCHAIN_RESET(sc);
	jme_txeof(sc);
	/*
	 * Free RX and TX mbufs still in the queues.
	 */
	for (i = 0; i < JME_RX_RING_CNT; i++) {
		rxd = &sc->jme_cdata.jme_rxdesc[i];
		if (rxd->rx_m != NULL) {
			bus_dmamap_sync(sc->jme_cdata.jme_rx_tag,
			    rxd->rx_dmamap, BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->jme_cdata.jme_rx_tag,
			    rxd->rx_dmamap);
			m_freem(rxd->rx_m);
			rxd->rx_m = NULL;
		}
        }
	for (i = 0; i < JME_TX_RING_CNT; i++) {
		txd = &sc->jme_cdata.jme_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->jme_cdata.jme_tx_tag,
			    txd->tx_dmamap, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->jme_cdata.jme_tx_tag,
			    txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
			txd->tx_ndesc = 0;
		}
        }
	jme_stats_update(sc);
	jme_stats_save(sc);
}