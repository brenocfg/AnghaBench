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
struct bwi_txbuf_data {struct bwi_txbuf* tbd_buf; } ;
struct bwi_txbuf {int /*<<< orphan*/  tb_dmap; int /*<<< orphan*/ * tb_ni; int /*<<< orphan*/ * tb_mbuf; } ;
struct bwi_rxbuf_data {struct bwi_rxbuf* rbd_buf; int /*<<< orphan*/  rbd_tmp_dmap; } ;
struct bwi_softc {int /*<<< orphan*/ * sc_buf_dtag; struct bwi_rxbuf_data sc_rx_bdata; struct bwi_txbuf_data* sc_tx_bdata; } ;
struct bwi_rxbuf {int /*<<< orphan*/  rb_dmap; int /*<<< orphan*/ * rb_mbuf; } ;

/* Variables and functions */
 int BWI_RX_NDESC ; 
 int BWI_TX_NDESC ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwi_dma_mbuf_destroy(struct bwi_softc *sc, int ntx, int nrx)
{
	int i, j;

	if (sc->sc_buf_dtag == NULL)
		return;

	for (i = 0; i < ntx; ++i) {
		struct bwi_txbuf_data *tbd = &sc->sc_tx_bdata[i];

		for (j = 0; j < BWI_TX_NDESC; ++j) {
			struct bwi_txbuf *tb = &tbd->tbd_buf[j];

			if (tb->tb_mbuf != NULL) {
				bus_dmamap_unload(sc->sc_buf_dtag,
						  tb->tb_dmap);
				m_freem(tb->tb_mbuf);
			}
			if (tb->tb_ni != NULL)
				ieee80211_free_node(tb->tb_ni);
			bus_dmamap_destroy(sc->sc_buf_dtag, tb->tb_dmap);
		}
	}

	if (nrx) {
		struct bwi_rxbuf_data *rbd = &sc->sc_rx_bdata;

		bus_dmamap_destroy(sc->sc_buf_dtag, rbd->rbd_tmp_dmap);
		for (j = 0; j < BWI_RX_NDESC; ++j) {
			struct bwi_rxbuf *rb = &rbd->rbd_buf[j];

			if (rb->rb_mbuf != NULL) {
				bus_dmamap_unload(sc->sc_buf_dtag,
						  rb->rb_dmap);
				m_freem(rb->rb_mbuf);
			}
			bus_dmamap_destroy(sc->sc_buf_dtag, rb->rb_dmap);
		}
	}

	bus_dma_tag_destroy(sc->sc_buf_dtag);
	sc->sc_buf_dtag = NULL;
}