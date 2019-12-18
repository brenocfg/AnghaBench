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
struct age_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_2__ {int /*<<< orphan*/  age_tx_tag; struct age_txdesc* age_txdesc; int /*<<< orphan*/  age_rx_tag; struct age_rxdesc* age_rxdesc; int /*<<< orphan*/ * age_rxhead; } ;
struct age_softc {TYPE_1__ age_cdata; int /*<<< orphan*/  age_dev; scalar_t__ age_watchdog_timer; int /*<<< orphan*/  age_tick_ch; int /*<<< orphan*/  age_flags; struct ifnet* age_ifp; } ;
struct age_rxdesc {int /*<<< orphan*/ * rx_m; int /*<<< orphan*/  rx_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_CSMB_CTRL ; 
 int /*<<< orphan*/  AGE_DMA_CFG ; 
 int /*<<< orphan*/  AGE_FLAG_LINK ; 
 int /*<<< orphan*/  AGE_IDLE_STATUS ; 
 int /*<<< orphan*/  AGE_INTR_MASK ; 
 int /*<<< orphan*/  AGE_INTR_STATUS ; 
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int AGE_RESET_TIMEOUT ; 
 int /*<<< orphan*/  AGE_RXCHAIN_RESET (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_RXQ_CFG ; 
 int AGE_RX_RING_CNT ; 
 int /*<<< orphan*/  AGE_TXQ_CFG ; 
 int AGE_TX_RING_CNT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_4 (struct age_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int DMA_CFG_RD_ENB ; 
 int DMA_CFG_WR_ENB ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int RXQ_CFG_ENB ; 
 int TXQ_CFG_ENB ; 
 int /*<<< orphan*/  age_stop_rxmac (struct age_softc*) ; 
 int /*<<< orphan*/  age_stop_txmac (struct age_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
age_stop(struct age_softc *sc)
{
	struct ifnet *ifp;
	struct age_txdesc *txd;
	struct age_rxdesc *rxd;
	uint32_t reg;
	int i;

	AGE_LOCK_ASSERT(sc);
	/*
	 * Mark the interface down and cancel the watchdog timer.
	 */
	ifp = sc->age_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->age_flags &= ~AGE_FLAG_LINK;
	callout_stop(&sc->age_tick_ch);
	sc->age_watchdog_timer = 0;

	/*
	 * Disable interrupts.
	 */
	CSR_WRITE_4(sc, AGE_INTR_MASK, 0);
	CSR_WRITE_4(sc, AGE_INTR_STATUS, 0xFFFFFFFF);
	/* Stop CMB/SMB updates. */
	CSR_WRITE_4(sc, AGE_CSMB_CTRL, 0);
	/* Stop Rx/Tx MAC. */
	age_stop_rxmac(sc);
	age_stop_txmac(sc);
	/* Stop DMA. */
	CSR_WRITE_4(sc, AGE_DMA_CFG,
	    CSR_READ_4(sc, AGE_DMA_CFG) & ~(DMA_CFG_RD_ENB | DMA_CFG_WR_ENB));
	/* Stop TxQ/RxQ. */
	CSR_WRITE_4(sc, AGE_TXQ_CFG,
	    CSR_READ_4(sc, AGE_TXQ_CFG) & ~TXQ_CFG_ENB);
	CSR_WRITE_4(sc, AGE_RXQ_CFG,
	    CSR_READ_4(sc, AGE_RXQ_CFG) & ~RXQ_CFG_ENB);
	for (i = AGE_RESET_TIMEOUT; i > 0; i--) {
		if ((reg = CSR_READ_4(sc, AGE_IDLE_STATUS)) == 0)
			break;
		DELAY(10);
	}
	if (i == 0)
		device_printf(sc->age_dev,
		    "stopping Rx/Tx MACs timed out(0x%08x)!\n", reg);

	 /* Reclaim Rx buffers that have been processed. */
	if (sc->age_cdata.age_rxhead != NULL)
		m_freem(sc->age_cdata.age_rxhead);
	AGE_RXCHAIN_RESET(sc);
	/*
	 * Free RX and TX mbufs still in the queues.
	 */
	for (i = 0; i < AGE_RX_RING_CNT; i++) {
		rxd = &sc->age_cdata.age_rxdesc[i];
		if (rxd->rx_m != NULL) {
			bus_dmamap_sync(sc->age_cdata.age_rx_tag,
			    rxd->rx_dmamap, BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->age_cdata.age_rx_tag,
			    rxd->rx_dmamap);
			m_freem(rxd->rx_m);
			rxd->rx_m = NULL;
		}
        }
	for (i = 0; i < AGE_TX_RING_CNT; i++) {
		txd = &sc->age_cdata.age_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->age_cdata.age_tx_tag,
			    txd->tx_dmamap, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->age_cdata.age_tx_tag,
			    txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
		}
        }
}