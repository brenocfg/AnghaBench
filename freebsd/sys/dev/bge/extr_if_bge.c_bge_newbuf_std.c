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
struct TYPE_7__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; scalar_t__ m_len; } ;
struct TYPE_10__ {int /*<<< orphan*/ * bge_rx_std_dmamap; int /*<<< orphan*/  bge_rx_mtag; int /*<<< orphan*/ * bge_rx_std_seglen; struct mbuf** bge_rx_std_chain; int /*<<< orphan*/  bge_rx_std_sparemap; } ;
struct TYPE_8__ {struct bge_rx_bd* bge_rx_std_ring; } ;
struct bge_softc {int bge_flags; size_t bge_std; TYPE_4__ bge_cdata; TYPE_2__ bge_ldata; int /*<<< orphan*/  bge_ifp; } ;
struct TYPE_9__ {int /*<<< orphan*/  bge_addr_hi; int /*<<< orphan*/  bge_addr_lo; } ;
struct bge_rx_bd {int bge_idx; int /*<<< orphan*/  bge_len; int /*<<< orphan*/  bge_flags; TYPE_3__ bge_addr; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_ADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int BGE_FLAG_JUMBO_STD ; 
 int BGE_FLAG_RX_ALIGNBUG ; 
 int /*<<< orphan*/  BGE_RXBDFLAG_END ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int ENOBUFS ; 
 scalar_t__ ETHER_ALIGN ; 
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 scalar_t__ MCLBYTES ; 
 scalar_t__ MJUM9BYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_5__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ if_getmtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* m_getjcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
bge_newbuf_std(struct bge_softc *sc, int i)
{
	struct mbuf *m;
	struct bge_rx_bd *r;
	bus_dma_segment_t segs[1];
	bus_dmamap_t map;
	int error, nsegs;

	if (sc->bge_flags & BGE_FLAG_JUMBO_STD &&
	    (if_getmtu(sc->bge_ifp) + ETHER_HDR_LEN + ETHER_CRC_LEN +
	    ETHER_VLAN_ENCAP_LEN > (MCLBYTES - ETHER_ALIGN))) {
		m = m_getjcl(M_NOWAIT, MT_DATA, M_PKTHDR, MJUM9BYTES);
		if (m == NULL)
			return (ENOBUFS);
		m->m_len = m->m_pkthdr.len = MJUM9BYTES;
	} else {
		m = m_getcl(M_NOWAIT, MT_DATA, M_PKTHDR);
		if (m == NULL)
			return (ENOBUFS);
		m->m_len = m->m_pkthdr.len = MCLBYTES;
	}
	if ((sc->bge_flags & BGE_FLAG_RX_ALIGNBUG) == 0)
		m_adj(m, ETHER_ALIGN);

	error = bus_dmamap_load_mbuf_sg(sc->bge_cdata.bge_rx_mtag,
	    sc->bge_cdata.bge_rx_std_sparemap, m, segs, &nsegs, 0);
	if (error != 0) {
		m_freem(m);
		return (error);
	}
	if (sc->bge_cdata.bge_rx_std_chain[i] != NULL) {
		bus_dmamap_sync(sc->bge_cdata.bge_rx_mtag,
		    sc->bge_cdata.bge_rx_std_dmamap[i], BUS_DMASYNC_POSTREAD);
		bus_dmamap_unload(sc->bge_cdata.bge_rx_mtag,
		    sc->bge_cdata.bge_rx_std_dmamap[i]);
	}
	map = sc->bge_cdata.bge_rx_std_dmamap[i];
	sc->bge_cdata.bge_rx_std_dmamap[i] = sc->bge_cdata.bge_rx_std_sparemap;
	sc->bge_cdata.bge_rx_std_sparemap = map;
	sc->bge_cdata.bge_rx_std_chain[i] = m;
	sc->bge_cdata.bge_rx_std_seglen[i] = segs[0].ds_len;
	r = &sc->bge_ldata.bge_rx_std_ring[sc->bge_std];
	r->bge_addr.bge_addr_lo = BGE_ADDR_LO(segs[0].ds_addr);
	r->bge_addr.bge_addr_hi = BGE_ADDR_HI(segs[0].ds_addr);
	r->bge_flags = BGE_RXBDFLAG_END;
	r->bge_len = segs[0].ds_len;
	r->bge_idx = i;

	bus_dmamap_sync(sc->bge_cdata.bge_rx_mtag,
	    sc->bge_cdata.bge_rx_std_dmamap[i], BUS_DMASYNC_PREREAD);

	return (0);
}