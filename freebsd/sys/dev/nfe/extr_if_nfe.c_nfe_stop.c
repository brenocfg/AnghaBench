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
struct nfe_tx_ring {int /*<<< orphan*/  tx_data_tag; struct nfe_tx_data* data; } ;
struct nfe_tx_data {int /*<<< orphan*/ * m; int /*<<< orphan*/  tx_data_map; } ;
struct nfe_jrx_ring {int /*<<< orphan*/  jrx_data_tag; struct nfe_rx_data* jdata; } ;
struct nfe_rx_ring {int /*<<< orphan*/  rx_data_tag; struct nfe_rx_data* data; } ;
struct nfe_softc {int nfe_flags; struct nfe_tx_ring txq; struct nfe_jrx_ring jrxq; struct nfe_rx_ring rxq; scalar_t__ nfe_link; int /*<<< orphan*/  nfe_stat_ch; scalar_t__ nfe_watchdog_timer; } ;
struct nfe_rx_data {int /*<<< orphan*/ * m; int /*<<< orphan*/  rx_data_map; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int NFE_JUMBO_RX_RING_COUNT ; 
 int NFE_JUMBO_SUP ; 
 int /*<<< orphan*/  NFE_LOCK_ASSERT (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_RX_CTL ; 
 int NFE_RX_RING_COUNT ; 
 int /*<<< orphan*/  NFE_TX_CTL ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct nfe_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfe_disable_intr (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_stats_update (struct nfe_softc*) ; 

__attribute__((used)) static void
nfe_stop(if_t ifp)
{
	struct nfe_softc *sc = if_getsoftc(ifp);
	struct nfe_rx_ring *rx_ring;
	struct nfe_jrx_ring *jrx_ring;
	struct nfe_tx_ring *tx_ring;
	struct nfe_rx_data *rdata;
	struct nfe_tx_data *tdata;
	int i;

	NFE_LOCK_ASSERT(sc);

	sc->nfe_watchdog_timer = 0;
	if_setdrvflagbits(ifp, 0, (IFF_DRV_RUNNING | IFF_DRV_OACTIVE));

	callout_stop(&sc->nfe_stat_ch);

	/* abort Tx */
	NFE_WRITE(sc, NFE_TX_CTL, 0);

	/* disable Rx */
	NFE_WRITE(sc, NFE_RX_CTL, 0);

	/* disable interrupts */
	nfe_disable_intr(sc);

	sc->nfe_link = 0;

	/* free Rx and Tx mbufs still in the queues. */
	rx_ring = &sc->rxq;
	for (i = 0; i < NFE_RX_RING_COUNT; i++) {
		rdata = &rx_ring->data[i];
		if (rdata->m != NULL) {
			bus_dmamap_sync(rx_ring->rx_data_tag,
			    rdata->rx_data_map, BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(rx_ring->rx_data_tag,
			    rdata->rx_data_map);
			m_freem(rdata->m);
			rdata->m = NULL;
		}
	}

	if ((sc->nfe_flags & NFE_JUMBO_SUP) != 0) {
		jrx_ring = &sc->jrxq;
		for (i = 0; i < NFE_JUMBO_RX_RING_COUNT; i++) {
			rdata = &jrx_ring->jdata[i];
			if (rdata->m != NULL) {
				bus_dmamap_sync(jrx_ring->jrx_data_tag,
				    rdata->rx_data_map, BUS_DMASYNC_POSTREAD);
				bus_dmamap_unload(jrx_ring->jrx_data_tag,
				    rdata->rx_data_map);
				m_freem(rdata->m);
				rdata->m = NULL;
			}
		}
	}

	tx_ring = &sc->txq;
	for (i = 0; i < NFE_RX_RING_COUNT; i++) {
		tdata = &tx_ring->data[i];
		if (tdata->m != NULL) {
			bus_dmamap_sync(tx_ring->tx_data_tag,
			    tdata->tx_data_map, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(tx_ring->tx_data_tag,
			    tdata->tx_data_map);
			m_freem(tdata->m);
			tdata->m = NULL;
		}
	}
	/* Update hardware stats. */
	nfe_stats_update(sc);
}