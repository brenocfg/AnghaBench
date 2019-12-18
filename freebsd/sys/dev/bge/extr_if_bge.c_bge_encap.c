#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_10__ {int csum_flags; scalar_t__ len; scalar_t__ ether_vtag; } ;
struct mbuf {int m_flags; TYPE_4__ m_pkthdr; int /*<<< orphan*/ * m_next; } ;
struct TYPE_8__ {scalar_t__ bge_addr_lo; void* bge_addr_hi; } ;
struct bge_tx_bd {scalar_t__ bge_len; scalar_t__ bge_flags; scalar_t__ bge_mss; scalar_t__ bge_vlan_tag; TYPE_2__ bge_addr; } ;
struct TYPE_9__ {struct mbuf** bge_tx_chain; int /*<<< orphan*/ * bge_tx_dmamap; int /*<<< orphan*/  bge_tx_mtag; } ;
struct TYPE_7__ {struct bge_tx_bd* bge_tx_ring; } ;
struct bge_softc {int bge_flags; int bge_csum_features; int bge_forced_collapse; scalar_t__ bge_txcnt; scalar_t__ bge_asicrev; TYPE_3__ bge_cdata; TYPE_1__ bge_ldata; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_11__ {scalar_t__ ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;

/* Variables and functions */
 void* BGE_ADDR_HI (int /*<<< orphan*/ ) ; 
 void* BGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 scalar_t__ BGE_ASICREV_BCM5762 ; 
 int BGE_FLAG_JUMBO_FRAME ; 
 int BGE_FLAG_PCIE ; 
 int BGE_FLAG_SHORT_DMA_BUG ; 
 int /*<<< orphan*/  BGE_INC (size_t,scalar_t__) ; 
 int BGE_NSEG_NEW ; 
 scalar_t__ BGE_TXBDFLAG_CPU_POST_DMA ; 
 scalar_t__ BGE_TXBDFLAG_CPU_PRE_DMA ; 
 scalar_t__ BGE_TXBDFLAG_END ; 
 scalar_t__ BGE_TXBDFLAG_IP_CSUM ; 
 scalar_t__ BGE_TXBDFLAG_JUMBO_FRAME ; 
 scalar_t__ BGE_TXBDFLAG_TCP_UDP_CSUM ; 
 scalar_t__ BGE_TXBDFLAG_VLAN_TAG ; 
 scalar_t__ BGE_TX_RING_CNT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int EFBIG ; 
 int EIO ; 
 int ENOBUFS ; 
 scalar_t__ ETHER_MAX_LEN ; 
 scalar_t__ ETHER_MIN_NOPAD ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_VLANTAG ; 
 struct mbuf* bge_check_short_dma (struct mbuf*) ; 
 int bge_cksum_pad (struct mbuf*) ; 
 struct mbuf* bge_setup_tso (struct bge_softc*,struct mbuf*,scalar_t__*,scalar_t__*) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_5__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* m_collapse (struct mbuf*,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
bge_encap(struct bge_softc *sc, struct mbuf **m_head, uint32_t *txidx)
{
	bus_dma_segment_t	segs[BGE_NSEG_NEW];
	bus_dmamap_t		map;
	struct bge_tx_bd	*d;
	struct mbuf		*m = *m_head;
	uint32_t		idx = *txidx;
	uint16_t		csum_flags, mss, vlan_tag;
	int			nsegs, i, error;

	csum_flags = 0;
	mss = 0;
	vlan_tag = 0;
	if ((sc->bge_flags & BGE_FLAG_SHORT_DMA_BUG) != 0 &&
	    m->m_next != NULL) {
		*m_head = bge_check_short_dma(m);
		if (*m_head == NULL)
			return (ENOBUFS);
		m = *m_head;
	}
	if ((m->m_pkthdr.csum_flags & CSUM_TSO) != 0) {
		*m_head = m = bge_setup_tso(sc, m, &mss, &csum_flags);
		if (*m_head == NULL)
			return (ENOBUFS);
		csum_flags |= BGE_TXBDFLAG_CPU_PRE_DMA |
		    BGE_TXBDFLAG_CPU_POST_DMA;
	} else if ((m->m_pkthdr.csum_flags & sc->bge_csum_features) != 0) {
		if (m->m_pkthdr.csum_flags & CSUM_IP)
			csum_flags |= BGE_TXBDFLAG_IP_CSUM;
		if (m->m_pkthdr.csum_flags & (CSUM_TCP | CSUM_UDP)) {
			csum_flags |= BGE_TXBDFLAG_TCP_UDP_CSUM;
			if (m->m_pkthdr.len < ETHER_MIN_NOPAD &&
			    (error = bge_cksum_pad(m)) != 0) {
				m_freem(m);
				*m_head = NULL;
				return (error);
			}
		}
	}

	if ((m->m_pkthdr.csum_flags & CSUM_TSO) == 0) {
		if (sc->bge_flags & BGE_FLAG_JUMBO_FRAME &&
		    m->m_pkthdr.len > ETHER_MAX_LEN)
			csum_flags |= BGE_TXBDFLAG_JUMBO_FRAME;
		if (sc->bge_forced_collapse > 0 &&
		    (sc->bge_flags & BGE_FLAG_PCIE) != 0 && m->m_next != NULL) {
			/*
			 * Forcedly collapse mbuf chains to overcome hardware
			 * limitation which only support a single outstanding
			 * DMA read operation.
			 */
			if (sc->bge_forced_collapse == 1)
				m = m_defrag(m, M_NOWAIT);
			else
				m = m_collapse(m, M_NOWAIT,
				    sc->bge_forced_collapse);
			if (m == NULL)
				m = *m_head;
			*m_head = m;
		}
	}

	map = sc->bge_cdata.bge_tx_dmamap[idx];
	error = bus_dmamap_load_mbuf_sg(sc->bge_cdata.bge_tx_mtag, map, m, segs,
	    &nsegs, BUS_DMA_NOWAIT);
	if (error == EFBIG) {
		m = m_collapse(m, M_NOWAIT, BGE_NSEG_NEW);
		if (m == NULL) {
			m_freem(*m_head);
			*m_head = NULL;
			return (ENOBUFS);
		}
		*m_head = m;
		error = bus_dmamap_load_mbuf_sg(sc->bge_cdata.bge_tx_mtag, map,
		    m, segs, &nsegs, BUS_DMA_NOWAIT);
		if (error) {
			m_freem(m);
			*m_head = NULL;
			return (error);
		}
	} else if (error != 0)
		return (error);

	/* Check if we have enough free send BDs. */
	if (sc->bge_txcnt + nsegs >= BGE_TX_RING_CNT) {
		bus_dmamap_unload(sc->bge_cdata.bge_tx_mtag, map);
		return (ENOBUFS);
	}

	bus_dmamap_sync(sc->bge_cdata.bge_tx_mtag, map, BUS_DMASYNC_PREWRITE);

	if (m->m_flags & M_VLANTAG) {
		csum_flags |= BGE_TXBDFLAG_VLAN_TAG;
		vlan_tag = m->m_pkthdr.ether_vtag;
	}

	if (sc->bge_asicrev == BGE_ASICREV_BCM5762 &&
	    (m->m_pkthdr.csum_flags & CSUM_TSO) != 0) {
		/*
		 * 5725 family of devices corrupts TSO packets when TSO DMA
		 * buffers cross into regions which are within MSS bytes of
		 * a 4GB boundary.  If we encounter the condition, drop the
		 * packet.
		 */
		for (i = 0; ; i++) {
			d = &sc->bge_ldata.bge_tx_ring[idx];
			d->bge_addr.bge_addr_lo = BGE_ADDR_LO(segs[i].ds_addr);
			d->bge_addr.bge_addr_hi = BGE_ADDR_HI(segs[i].ds_addr);
			d->bge_len = segs[i].ds_len;
			if (d->bge_addr.bge_addr_lo + segs[i].ds_len + mss <
			    d->bge_addr.bge_addr_lo)
				break;
			d->bge_flags = csum_flags;
			d->bge_vlan_tag = vlan_tag;
			d->bge_mss = mss;
			if (i == nsegs - 1)
				break;
			BGE_INC(idx, BGE_TX_RING_CNT);
		}
		if (i != nsegs - 1) {
			bus_dmamap_sync(sc->bge_cdata.bge_tx_mtag, map,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->bge_cdata.bge_tx_mtag, map);
			m_freem(*m_head);
			*m_head = NULL;
			return (EIO);
		}
	} else {
		for (i = 0; ; i++) {
			d = &sc->bge_ldata.bge_tx_ring[idx];
			d->bge_addr.bge_addr_lo = BGE_ADDR_LO(segs[i].ds_addr);
			d->bge_addr.bge_addr_hi = BGE_ADDR_HI(segs[i].ds_addr);
			d->bge_len = segs[i].ds_len;
			d->bge_flags = csum_flags;
			d->bge_vlan_tag = vlan_tag;
			d->bge_mss = mss;
			if (i == nsegs - 1)
				break;
			BGE_INC(idx, BGE_TX_RING_CNT);
		}
	}

	/* Mark the last segment as end of packet... */
	d->bge_flags |= BGE_TXBDFLAG_END;

	/*
	 * Insure that the map for this transmission
	 * is placed at the array index of the last descriptor
	 * in this chain.
	 */
	sc->bge_cdata.bge_tx_dmamap[*txidx] = sc->bge_cdata.bge_tx_dmamap[idx];
	sc->bge_cdata.bge_tx_dmamap[idx] = map;
	sc->bge_cdata.bge_tx_chain[idx] = m;
	sc->bge_txcnt += nsegs;

	BGE_INC(idx, BGE_TX_RING_CNT);
	*txidx = idx;

	return (0);
}