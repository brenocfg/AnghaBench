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
struct bwi_rxbuf_data {struct bwi_rxbuf* rbd_buf; } ;
struct bwi_ring_data {int /*<<< orphan*/  rdata_txrx_ctrl; } ;
struct bwi_softc {int /*<<< orphan*/  sc_buf_dtag; struct bwi_rxbuf_data sc_rx_bdata; struct bwi_ring_data sc_rx_rdata; } ;
struct bwi_rxbuf {int /*<<< orphan*/ * rb_mbuf; int /*<<< orphan*/  rb_dmap; } ;

/* Variables and functions */
 int BWI_RX_NDESC ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_reset_rx_ring32 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwi_free_rx_ring32(struct bwi_softc *sc)
{
	struct bwi_ring_data *rd = &sc->sc_rx_rdata;
	struct bwi_rxbuf_data *rbd = &sc->sc_rx_bdata;
	int i;

	bwi_reset_rx_ring32(sc, rd->rdata_txrx_ctrl);

	for (i = 0; i < BWI_RX_NDESC; ++i) {
		struct bwi_rxbuf *rb = &rbd->rbd_buf[i];

		if (rb->rb_mbuf != NULL) {
			bus_dmamap_unload(sc->sc_buf_dtag, rb->rb_dmap);
			m_freem(rb->rb_mbuf);
			rb->rb_mbuf = NULL;
		}
	}
}