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
struct ffec_softc {size_t rx_idx; int /*<<< orphan*/  rxdesc_map; int /*<<< orphan*/  rxdesc_tag; struct ffec_hwdesc* rxdesc_ring; int /*<<< orphan*/  dev; } ;
struct ffec_hwdesc {int flags_len; int /*<<< orphan*/  buf_paddr; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  FEC_RDAR_RDAR ; 
 int /*<<< orphan*/  FEC_RDAR_REG ; 
 int FEC_RXDESC_EMPTY ; 
 int FEC_RXDESC_ERROR_BITS ; 
 int FEC_RXDESC_L ; 
 int FEC_RXDESC_LEN_MASK ; 
 int /*<<< orphan*/  FFEC_ASSERT_LOCKED (struct ffec_softc*) ; 
 int /*<<< orphan*/  WR4 (struct ffec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffec_rxfinish_onebuf (struct ffec_softc*,int) ; 
 int /*<<< orphan*/  ffec_setup_rxdesc (struct ffec_softc*,size_t,int /*<<< orphan*/ ) ; 
 size_t next_rxidx (struct ffec_softc*,size_t) ; 

__attribute__((used)) static void
ffec_rxfinish_locked(struct ffec_softc *sc)
{
	struct ffec_hwdesc *desc;
	int len;
	boolean_t produced_empty_buffer;

	FFEC_ASSERT_LOCKED(sc);

	/* XXX Can't set PRE|POST right now, but we need both. */
	bus_dmamap_sync(sc->rxdesc_tag, sc->rxdesc_map, BUS_DMASYNC_PREREAD);
	bus_dmamap_sync(sc->rxdesc_tag, sc->rxdesc_map, BUS_DMASYNC_POSTREAD);
	produced_empty_buffer = false;
	for (;;) {
		desc = &sc->rxdesc_ring[sc->rx_idx];
		if (desc->flags_len & FEC_RXDESC_EMPTY)
			break;
		produced_empty_buffer = true;
		len = (desc->flags_len & FEC_RXDESC_LEN_MASK);
		if (len < 64) {
			/*
			 * Just recycle the descriptor and continue.           .
			 */
			ffec_setup_rxdesc(sc, sc->rx_idx,
			    sc->rxdesc_ring[sc->rx_idx].buf_paddr);
		} else if ((desc->flags_len & FEC_RXDESC_L) == 0) {
			/*
			 * The entire frame is not in this buffer.  Impossible.
			 * Recycle the descriptor and continue.
			 *
			 * XXX what's the right way to handle this? Probably we
			 * should stop/init the hardware because this should
			 * just really never happen when we have buffers bigger
			 * than the maximum frame size.
			 */
			device_printf(sc->dev, 
			    "fec_rxfinish: received frame without LAST bit set");
			ffec_setup_rxdesc(sc, sc->rx_idx, 
			    sc->rxdesc_ring[sc->rx_idx].buf_paddr);
		} else if (desc->flags_len & FEC_RXDESC_ERROR_BITS) {
			/*
			 *  Something went wrong with receiving the frame, we
			 *  don't care what (the hardware has counted the error
			 *  in the stats registers already), we just reuse the
			 *  same mbuf, which is still dma-mapped, by resetting
			 *  the rx descriptor.
			 */
			ffec_setup_rxdesc(sc, sc->rx_idx, 
			    sc->rxdesc_ring[sc->rx_idx].buf_paddr);
		} else {
			/*
			 *  Normal case: a good frame all in one buffer.
			 */
			ffec_rxfinish_onebuf(sc, len);
		}
		sc->rx_idx = next_rxidx(sc, sc->rx_idx);
	}

	if (produced_empty_buffer) {
		bus_dmamap_sync(sc->rxdesc_tag, sc->rxdesc_map, BUS_DMASYNC_PREWRITE);
		WR4(sc, FEC_RDAR_REG, FEC_RDAR_RDAR);
		bus_dmamap_sync(sc->rxdesc_tag, sc->rxdesc_map, BUS_DMASYNC_POSTWRITE);
	}
}