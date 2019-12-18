#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct tsec_softc {size_t tx_idx_head; struct tsec_desc* tsec_tx_vaddr; int /*<<< orphan*/  tsec_tx_mtag; struct tsec_bufmap* tx_bufmap; } ;
struct tsec_desc {scalar_t__ flags; int /*<<< orphan*/  bufptr; int /*<<< orphan*/  length; } ;
struct tsec_bufmap {struct mbuf* mbuf; int /*<<< orphan*/  map; } ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; int /*<<< orphan*/  ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int EFBIG ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TSEC_TRANSMIT_LOCK_ASSERT (struct tsec_softc*) ; 
 scalar_t__ TSEC_TXBD_I ; 
 scalar_t__ TSEC_TXBD_L ; 
 scalar_t__ TSEC_TXBD_R ; 
 scalar_t__ TSEC_TXBD_TC ; 
 scalar_t__ TSEC_TXBD_TOE ; 
 scalar_t__ TSEC_TXBD_W ; 
 int TSEC_TX_MAX_DMA_SEGS ; 
 int TSEC_TX_NUM_DESC ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
tsec_encap(struct ifnet *ifp, struct tsec_softc *sc, struct mbuf *m0,
    uint16_t fcb_flags, int *start_tx)
{
	bus_dma_segment_t segs[TSEC_TX_MAX_DMA_SEGS];
	int error, i, nsegs;
	struct tsec_bufmap *tx_bufmap;
	uint32_t tx_idx;
	uint16_t flags;

	TSEC_TRANSMIT_LOCK_ASSERT(sc);

	tx_idx = sc->tx_idx_head;
	tx_bufmap = &sc->tx_bufmap[tx_idx];
 
	/* Create mapping in DMA memory */
	error = bus_dmamap_load_mbuf_sg(sc->tsec_tx_mtag, tx_bufmap->map, m0,
	    segs, &nsegs, BUS_DMA_NOWAIT);
	if (error == EFBIG) {
		/* Too many segments!  Defrag and try again. */
		struct mbuf *m = m_defrag(m0, M_NOWAIT);

		if (m == NULL) {
			m_freem(m0);
			return;
		}
		m0 = m;
		error = bus_dmamap_load_mbuf_sg(sc->tsec_tx_mtag,
		    tx_bufmap->map, m0, segs, &nsegs, BUS_DMA_NOWAIT);
	}
	if (error != 0) {
		/* Give up. */
		m_freem(m0);
		return;
	}

	bus_dmamap_sync(sc->tsec_tx_mtag, tx_bufmap->map,
	    BUS_DMASYNC_PREWRITE);
	tx_bufmap->mbuf = m0;
 
	/*
	 * Fill in the TX descriptors back to front so that READY bit in first
	 * descriptor is set last.
	 */
	tx_idx = (tx_idx + (uint32_t)nsegs) & (TSEC_TX_NUM_DESC - 1);
	sc->tx_idx_head = tx_idx;
	flags = TSEC_TXBD_L | TSEC_TXBD_I | TSEC_TXBD_R | TSEC_TXBD_TC;
	for (i = nsegs - 1; i >= 0; i--) {
		struct tsec_desc *tx_desc;

		tx_idx = (tx_idx - 1) & (TSEC_TX_NUM_DESC - 1);
		tx_desc = &sc->tsec_tx_vaddr[tx_idx];
		tx_desc->length = segs[i].ds_len;
		tx_desc->bufptr = segs[i].ds_addr;

		if (i == 0) {
			wmb();

			if (fcb_flags != 0)
				flags |= TSEC_TXBD_TOE;
		}

		/*
		 * Set flags:
		 *   - wrap
		 *   - checksum
		 *   - ready to send
		 *   - transmit the CRC sequence after the last data byte
		 *   - interrupt after the last buffer
		 */
		tx_desc->flags = (tx_idx == (TSEC_TX_NUM_DESC - 1) ?
		    TSEC_TXBD_W : 0) | flags;

		flags &= ~(TSEC_TXBD_L | TSEC_TXBD_I);
	}

	BPF_MTAP(ifp, m0);
	*start_tx = 1;
}