#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sis_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct sis_softc {int /*<<< orphan*/  sis_tx_tag; struct sis_txdesc* sis_txdesc; int /*<<< orphan*/  sis_rx_tag; struct sis_rxdesc* sis_rxdesc; int /*<<< orphan*/  sis_flags; int /*<<< orphan*/  sis_stat_ch; scalar_t__ sis_watchdog_timer; struct ifnet* sis_ifp; } ;
struct sis_rxdesc {int /*<<< orphan*/ * rx_m; int /*<<< orphan*/  rx_dmamap; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  SIS_CSR ; 
 int SIS_CSR_RX_DISABLE ; 
 int SIS_CSR_TX_DISABLE ; 
 int /*<<< orphan*/  SIS_FLAG_LINK ; 
 int /*<<< orphan*/  SIS_IER ; 
 int /*<<< orphan*/  SIS_IMR ; 
 int /*<<< orphan*/  SIS_ISR ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_RX_LISTPTR ; 
 int SIS_RX_LIST_CNT ; 
 int /*<<< orphan*/  SIS_SETBIT (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIS_TX_LISTPTR ; 
 int SIS_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sis_stop(struct sis_softc *sc)
{
	struct ifnet *ifp;
	struct sis_rxdesc *rxd;
	struct sis_txdesc *txd;
	int i;

	SIS_LOCK_ASSERT(sc);

	ifp = sc->sis_ifp;
	sc->sis_watchdog_timer = 0;

	callout_stop(&sc->sis_stat_ch);

	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	CSR_WRITE_4(sc, SIS_IER, 0);
	CSR_WRITE_4(sc, SIS_IMR, 0);
	CSR_READ_4(sc, SIS_ISR); /* clear any interrupts already pending */
	SIS_SETBIT(sc, SIS_CSR, SIS_CSR_TX_DISABLE|SIS_CSR_RX_DISABLE);
	DELAY(1000);
	CSR_WRITE_4(sc, SIS_TX_LISTPTR, 0);
	CSR_WRITE_4(sc, SIS_RX_LISTPTR, 0);

	sc->sis_flags &= ~SIS_FLAG_LINK;

	/*
	 * Free data in the RX lists.
	 */
	for (i = 0; i < SIS_RX_LIST_CNT; i++) {
		rxd = &sc->sis_rxdesc[i];
		if (rxd->rx_m != NULL) {
			bus_dmamap_sync(sc->sis_rx_tag, rxd->rx_dmamap,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->sis_rx_tag, rxd->rx_dmamap);
			m_freem(rxd->rx_m);
			rxd->rx_m = NULL;
		}
	}

	/*
	 * Free the TX list buffers.
	 */
	for (i = 0; i < SIS_TX_LIST_CNT; i++) {
		txd = &sc->sis_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->sis_tx_tag, txd->tx_dmamap,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->sis_tx_tag, txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
		}
	}
}