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
typedef  int uint32_t ;
struct ifnet {int if_drv_flags; } ;
struct ale_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_2__ {int /*<<< orphan*/  ale_tx_tag; struct ale_txdesc* ale_txdesc; } ;
struct ale_softc {TYPE_1__ ale_cdata; scalar_t__ ale_watchdog_timer; int /*<<< orphan*/  ale_tick_ch; int /*<<< orphan*/  ale_flags; struct ifnet* ale_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_DMA_CFG ; 
 int /*<<< orphan*/  ALE_FLAG_LINK ; 
 int /*<<< orphan*/  ALE_INTR_MASK ; 
 int /*<<< orphan*/  ALE_INTR_STATUS ; 
 int /*<<< orphan*/  ALE_LOCK_ASSERT (struct ale_softc*) ; 
 int /*<<< orphan*/  ALE_RXQ_CFG ; 
 int /*<<< orphan*/  ALE_TXQ_CFG ; 
 int ALE_TX_RING_CNT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_4 (struct ale_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ale_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int DMA_CFG_RXCMB_ENB ; 
 int DMA_CFG_TXCMB_ENB ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int RXQ_CFG_ENB ; 
 int TXQ_CFG_ENB ; 
 int /*<<< orphan*/  ale_stats_update (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_stop_mac (struct ale_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ale_stop(struct ale_softc *sc)
{
	struct ifnet *ifp;
	struct ale_txdesc *txd;
	uint32_t reg;
	int i;

	ALE_LOCK_ASSERT(sc);
	/*
	 * Mark the interface down and cancel the watchdog timer.
	 */
	ifp = sc->ale_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->ale_flags &= ~ALE_FLAG_LINK;
	callout_stop(&sc->ale_tick_ch);
	sc->ale_watchdog_timer = 0;
	ale_stats_update(sc);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, ALE_INTR_MASK, 0);
	CSR_WRITE_4(sc, ALE_INTR_STATUS, 0xFFFFFFFF);
	/* Disable queue processing and DMA. */
	reg = CSR_READ_4(sc, ALE_TXQ_CFG);
	reg &= ~TXQ_CFG_ENB;
	CSR_WRITE_4(sc, ALE_TXQ_CFG, reg);
	reg = CSR_READ_4(sc, ALE_RXQ_CFG);
	reg &= ~RXQ_CFG_ENB;
	CSR_WRITE_4(sc, ALE_RXQ_CFG, reg);
	reg = CSR_READ_4(sc, ALE_DMA_CFG);
	reg &= ~(DMA_CFG_TXCMB_ENB | DMA_CFG_RXCMB_ENB);
	CSR_WRITE_4(sc, ALE_DMA_CFG, reg);
	DELAY(1000);
	/* Stop Rx/Tx MACs. */
	ale_stop_mac(sc);
	/* Disable interrupts which might be touched in taskq handler. */
	CSR_WRITE_4(sc, ALE_INTR_STATUS, 0xFFFFFFFF);

	/*
	 * Free TX mbufs still in the queues.
	 */
	for (i = 0; i < ALE_TX_RING_CNT; i++) {
		txd = &sc->ale_cdata.ale_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->ale_cdata.ale_tx_tag,
			    txd->tx_dmamap, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->ale_cdata.ale_tx_tag,
			    txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
		}
        }
}