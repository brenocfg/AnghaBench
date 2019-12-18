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
struct glc_txsoft {int /*<<< orphan*/ * txs_mbuf; int /*<<< orphan*/  txs_dmamap; } ;
struct glc_softc {int first_used_txdma_slot; int /*<<< orphan*/  sc_tick_ch; scalar_t__ sc_wdog_timer; TYPE_1__* sc_ifp; int /*<<< orphan*/  sc_ifpflags; int /*<<< orphan*/  sc_self; struct glc_rxsoft* sc_rxsoft; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bus; scalar_t__ bsy_txdma_slots; int /*<<< orphan*/  sc_txfreeq; int /*<<< orphan*/  sc_txdma_tag; int /*<<< orphan*/  sc_txdirtyq; int /*<<< orphan*/  sc_rxdmadesc_map; int /*<<< orphan*/  sc_dmadesc_tag; int /*<<< orphan*/  sc_mtx; } ;
struct glc_rxsoft {int rxs_desc_slot; int /*<<< orphan*/  rxs_desc; int /*<<< orphan*/ * rxs_mbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_flags; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int GLC_MAX_RX_PACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct glc_txsoft* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct glc_txsoft*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct glc_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  glc_add_rxbuf (struct glc_softc*,int) ; 
 int /*<<< orphan*/  glc_add_rxbuf_dma (struct glc_softc*,int) ; 
 int /*<<< orphan*/  glc_set_multicast (struct glc_softc*) ; 
 int /*<<< orphan*/  glc_tick ; 
 int /*<<< orphan*/  hz ; 
 int lv1_net_start_rx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_net_stop_rx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_net_stop_tx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txs_q ; 

__attribute__((used)) static void
glc_init_locked(struct glc_softc *sc)
{
	int i, error;
	struct glc_rxsoft *rxs;
	struct glc_txsoft *txs;

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	lv1_net_stop_tx_dma(sc->sc_bus, sc->sc_dev, 0);
	lv1_net_stop_rx_dma(sc->sc_bus, sc->sc_dev, 0);

	glc_set_multicast(sc);

	for (i = 0; i < GLC_MAX_RX_PACKETS; i++) {
		rxs = &sc->sc_rxsoft[i];
		rxs->rxs_desc_slot = i;

		if (rxs->rxs_mbuf == NULL) {
			glc_add_rxbuf(sc, i);

			if (rxs->rxs_mbuf == NULL) {
				rxs->rxs_desc_slot = -1;
				break;
			}
		}

		glc_add_rxbuf_dma(sc, i);
		bus_dmamap_sync(sc->sc_dmadesc_tag, sc->sc_rxdmadesc_map,
		    BUS_DMASYNC_PREREAD);
	}

	/* Clear TX dirty queue */
	while ((txs = STAILQ_FIRST(&sc->sc_txdirtyq)) != NULL) {
		STAILQ_REMOVE_HEAD(&sc->sc_txdirtyq, txs_q);
		bus_dmamap_unload(sc->sc_txdma_tag, txs->txs_dmamap);

		if (txs->txs_mbuf != NULL) {
			m_freem(txs->txs_mbuf);
			txs->txs_mbuf = NULL;
		}

		STAILQ_INSERT_TAIL(&sc->sc_txfreeq, txs, txs_q);
	}
	sc->first_used_txdma_slot = -1;
	sc->bsy_txdma_slots = 0;

	error = lv1_net_start_rx_dma(sc->sc_bus, sc->sc_dev,
	    sc->sc_rxsoft[0].rxs_desc, 0);
	if (error != 0)
		device_printf(sc->sc_self,
		    "lv1_net_start_rx_dma error: %d\n", error);

	sc->sc_ifp->if_drv_flags |= IFF_DRV_RUNNING;
	sc->sc_ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	sc->sc_ifpflags = sc->sc_ifp->if_flags;

	sc->sc_wdog_timer = 0;
	callout_reset(&sc->sc_tick_ch, hz, glc_tick, sc);
}