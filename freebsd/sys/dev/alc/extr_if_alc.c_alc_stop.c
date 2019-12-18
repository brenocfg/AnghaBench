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
struct alc_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_2__ {int /*<<< orphan*/  alc_tx_tag; struct alc_txdesc* alc_txdesc; int /*<<< orphan*/  alc_rx_tag; struct alc_rxdesc* alc_rxdesc; int /*<<< orphan*/ * alc_rxhead; } ;
struct alc_softc {TYPE_1__ alc_cdata; scalar_t__ alc_watchdog_timer; int /*<<< orphan*/  alc_tick_ch; int /*<<< orphan*/  alc_flags; struct ifnet* alc_ifp; } ;
struct alc_rxdesc {int /*<<< orphan*/ * rx_m; int /*<<< orphan*/  rx_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_DMA_CFG ; 
 int /*<<< orphan*/  ALC_FLAG_LINK ; 
 int /*<<< orphan*/  ALC_INTR_MASK ; 
 int /*<<< orphan*/  ALC_INTR_STATUS ; 
 int /*<<< orphan*/  ALC_LOCK_ASSERT (struct alc_softc*) ; 
 int /*<<< orphan*/  ALC_RXCHAIN_RESET (struct alc_softc*) ; 
 int ALC_RX_RING_CNT ; 
 int ALC_TX_RING_CNT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int DMA_CFG_CMB_ENB ; 
 int DMA_CFG_SMB_DIS ; 
 int DMA_CFG_SMB_ENB ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFM_UNKNOWN ; 
 int /*<<< orphan*/  alc_aspm (struct alc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_stats_update (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_stop_mac (struct alc_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
alc_stop(struct alc_softc *sc)
{
	struct ifnet *ifp;
	struct alc_txdesc *txd;
	struct alc_rxdesc *rxd;
	uint32_t reg;
	int i;

	ALC_LOCK_ASSERT(sc);
	/*
	 * Mark the interface down and cancel the watchdog timer.
	 */
	ifp = sc->alc_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->alc_flags &= ~ALC_FLAG_LINK;
	callout_stop(&sc->alc_tick_ch);
	sc->alc_watchdog_timer = 0;
	alc_stats_update(sc);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, ALC_INTR_MASK, 0);
	CSR_WRITE_4(sc, ALC_INTR_STATUS, 0xFFFFFFFF);
	/* Disable DMA. */
	reg = CSR_READ_4(sc, ALC_DMA_CFG);
	reg &= ~(DMA_CFG_CMB_ENB | DMA_CFG_SMB_ENB);
	reg |= DMA_CFG_SMB_DIS;
	CSR_WRITE_4(sc, ALC_DMA_CFG, reg);
	DELAY(1000);
	/* Stop Rx/Tx MACs. */
	alc_stop_mac(sc);
	/* Disable interrupts which might be touched in taskq handler. */
	CSR_WRITE_4(sc, ALC_INTR_STATUS, 0xFFFFFFFF);
	/* Disable L0s/L1s */
	alc_aspm(sc, 0, IFM_UNKNOWN);
	/* Reclaim Rx buffers that have been processed. */
	if (sc->alc_cdata.alc_rxhead != NULL)
		m_freem(sc->alc_cdata.alc_rxhead);
	ALC_RXCHAIN_RESET(sc);
	/*
	 * Free Tx/Rx mbufs still in the queues.
	 */
	for (i = 0; i < ALC_RX_RING_CNT; i++) {
		rxd = &sc->alc_cdata.alc_rxdesc[i];
		if (rxd->rx_m != NULL) {
			bus_dmamap_sync(sc->alc_cdata.alc_rx_tag,
			    rxd->rx_dmamap, BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->alc_cdata.alc_rx_tag,
			    rxd->rx_dmamap);
			m_freem(rxd->rx_m);
			rxd->rx_m = NULL;
		}
	}
	for (i = 0; i < ALC_TX_RING_CNT; i++) {
		txd = &sc->alc_cdata.alc_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->alc_cdata.alc_tx_tag,
			    txd->tx_dmamap, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->alc_cdata.alc_tx_tag,
			    txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
		}
	}
}