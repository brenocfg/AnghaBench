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
struct et_softc {int /*<<< orphan*/  sc_rx_tag; struct et_rxbuf_data* sc_rx_data; struct et_rxdesc_ring* sc_rx_ring; int /*<<< orphan*/  sc_rx_mini_tag; } ;
struct et_rxdesc_ring {int /*<<< orphan*/  rr_dmap; } ;
struct et_rxbuf_data {struct et_rxbuf* rbd_buf; } ;
struct et_rxbuf {int /*<<< orphan*/ * rb_mbuf; int /*<<< orphan*/  rb_dmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int ET_RX_NDESC ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
et_free_rx_ring(struct et_softc *sc)
{
	struct et_rxbuf_data *rbd;
	struct et_rxdesc_ring *rx_ring;
	struct et_rxbuf *rb;
	int i;

	/* Ring 0 */
	rx_ring = &sc->sc_rx_ring[0];
	rbd = &sc->sc_rx_data[0];
	for (i = 0; i < ET_RX_NDESC; ++i) {
		rb = &rbd->rbd_buf[i];
		if (rb->rb_mbuf != NULL) {
			bus_dmamap_sync(sc->sc_rx_mini_tag, rx_ring->rr_dmap,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->sc_rx_mini_tag, rb->rb_dmap);
			m_freem(rb->rb_mbuf);
			rb->rb_mbuf = NULL;
		}
	}

	/* Ring 1 */
	rx_ring = &sc->sc_rx_ring[1];
	rbd = &sc->sc_rx_data[1];
	for (i = 0; i < ET_RX_NDESC; ++i) {
		rb = &rbd->rbd_buf[i];
		if (rb->rb_mbuf != NULL) {
			bus_dmamap_sync(sc->sc_rx_tag, rx_ring->rr_dmap,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->sc_rx_tag, rb->rb_dmap);
			m_freem(rb->rb_mbuf);
			rb->rb_mbuf = NULL;
		}
	}
}