#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct mbuf {int /*<<< orphan*/  m_len; TYPE_1__ m_pkthdr; } ;
struct eth_rx_sge {void* addr_lo; void* addr_hi; } ;
struct bxe_sw_rx_bd {struct mbuf* m; int /*<<< orphan*/ * m_map; } ;
struct TYPE_6__ {int /*<<< orphan*/  mbuf_alloc_sge; int /*<<< orphan*/  mbuf_rx_sge_mapping_failed; int /*<<< orphan*/  mbuf_rx_sge_alloc_failed; } ;
struct bxe_fastpath {struct eth_rx_sge* rx_sge_chain; int /*<<< orphan*/  rx_sge_mbuf_tag; int /*<<< orphan*/ * rx_sge_mbuf_spare_map; struct bxe_sw_rx_bd* rx_sge_mbuf_chain; TYPE_2__ eth_q_stats; } ;
typedef  int /*<<< orphan*/ * bus_dmamap_t ;
struct TYPE_7__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  SGE_PAGE_SIZE ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,TYPE_3__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getjcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_alloc_rx_sge_mbuf(struct bxe_fastpath *fp,
                      uint16_t            index)
{
    struct bxe_sw_rx_bd *sge_buf;
    struct eth_rx_sge *sge;
    bus_dma_segment_t segs[1];
    bus_dmamap_t map;
    struct mbuf *m;
    int nsegs;
    int rc = 0;

    /* allocate a new SGE mbuf */
    m = m_getjcl(M_NOWAIT, MT_DATA, M_PKTHDR, SGE_PAGE_SIZE);
    if (__predict_false(m == NULL)) {
        fp->eth_q_stats.mbuf_rx_sge_alloc_failed++;
        return (ENOMEM);
    }

    fp->eth_q_stats.mbuf_alloc_sge++;

    /* initialize the mbuf buffer length */
    m->m_pkthdr.len = m->m_len = SGE_PAGE_SIZE;

    /* map the SGE mbuf into non-paged pool */
    rc = bus_dmamap_load_mbuf_sg(fp->rx_sge_mbuf_tag,
                                 fp->rx_sge_mbuf_spare_map,
                                 m, segs, &nsegs, BUS_DMA_NOWAIT);
    if (__predict_false(rc != 0)) {
        fp->eth_q_stats.mbuf_rx_sge_mapping_failed++;
        m_freem(m);
        fp->eth_q_stats.mbuf_alloc_sge--;
        return (rc);
    }

    /* all mbufs must map to a single segment */
    KASSERT((nsegs == 1), ("Too many segments, %d returned!", nsegs));

    sge_buf = &fp->rx_sge_mbuf_chain[index];

    /* release any existing SGE mbuf mapping */
    if (sge_buf->m_map != NULL) {
        bus_dmamap_sync(fp->rx_sge_mbuf_tag, sge_buf->m_map,
                        BUS_DMASYNC_POSTREAD);
        bus_dmamap_unload(fp->rx_sge_mbuf_tag, sge_buf->m_map);
    }

    /* save the mbuf and mapping info for a future packet */
    map = sge_buf->m_map;
    sge_buf->m_map = fp->rx_sge_mbuf_spare_map;
    fp->rx_sge_mbuf_spare_map = map;
    bus_dmamap_sync(fp->rx_sge_mbuf_tag, sge_buf->m_map,
                    BUS_DMASYNC_PREREAD);
    sge_buf->m = m;

    sge = &fp->rx_sge_chain[index];
    sge->addr_hi = htole32(U64_HI(segs[0].ds_addr));
    sge->addr_lo = htole32(U64_LO(segs[0].ds_addr));

    return (rc);
}