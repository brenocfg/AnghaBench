#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct mbuf {int /*<<< orphan*/  m_len; TYPE_1__ m_pkthdr; } ;
struct TYPE_6__ {struct mbuf* m; int /*<<< orphan*/ * m_map; } ;
struct bxe_sw_tpa_info {int /*<<< orphan*/  seg; TYPE_3__ bd; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbuf_alloc_tpa; int /*<<< orphan*/  mbuf_rx_tpa_mapping_failed; int /*<<< orphan*/  mbuf_rx_tpa_alloc_failed; } ;
struct bxe_fastpath {int /*<<< orphan*/  rx_mbuf_tag; int /*<<< orphan*/ * rx_tpa_info_mbuf_spare_map; TYPE_2__ eth_q_stats; int /*<<< orphan*/  rx_buf_size; int /*<<< orphan*/  mbuf_alloc_size; struct bxe_sw_tpa_info* rx_tpa_info; } ;
typedef  int /*<<< orphan*/ * bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 scalar_t__ __predict_false (int) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 struct mbuf* m_getjcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_alloc_rx_tpa_mbuf(struct bxe_fastpath *fp,
                      int                 queue)
{
    struct bxe_sw_tpa_info *tpa_info = &fp->rx_tpa_info[queue];
    bus_dma_segment_t segs[1];
    bus_dmamap_t map;
    struct mbuf *m;
    int nsegs;
    int rc = 0;

    /* allocate the new TPA mbuf */
    m = m_getjcl(M_NOWAIT, MT_DATA, M_PKTHDR, fp->mbuf_alloc_size);
    if (__predict_false(m == NULL)) {
        fp->eth_q_stats.mbuf_rx_tpa_alloc_failed++;
        return (ENOBUFS);
    }

    fp->eth_q_stats.mbuf_alloc_tpa++;

    /* initialize the mbuf buffer length */
    m->m_pkthdr.len = m->m_len = fp->rx_buf_size;

    /* map the mbuf into non-paged pool */
    rc = bus_dmamap_load_mbuf_sg(fp->rx_mbuf_tag,
                                 fp->rx_tpa_info_mbuf_spare_map,
                                 m, segs, &nsegs, BUS_DMA_NOWAIT);
    if (__predict_false(rc != 0)) {
        fp->eth_q_stats.mbuf_rx_tpa_mapping_failed++;
        m_free(m);
        fp->eth_q_stats.mbuf_alloc_tpa--;
        return (rc);
    }

    /* all mbufs must map to a single segment */
    KASSERT((nsegs == 1), ("Too many segments, %d returned!", nsegs));

    /* release any existing TPA mbuf mapping */
    if (tpa_info->bd.m_map != NULL) {
        bus_dmamap_sync(fp->rx_mbuf_tag, tpa_info->bd.m_map,
                        BUS_DMASYNC_POSTREAD);
        bus_dmamap_unload(fp->rx_mbuf_tag, tpa_info->bd.m_map);
    }

    /* save the mbuf and mapping info for the TPA mbuf */
    map = tpa_info->bd.m_map;
    tpa_info->bd.m_map = fp->rx_tpa_info_mbuf_spare_map;
    fp->rx_tpa_info_mbuf_spare_map = map;
    bus_dmamap_sync(fp->rx_mbuf_tag, tpa_info->bd.m_map,
                    BUS_DMASYNC_PREREAD);
    tpa_info->bd.m = m;
    tpa_info->seg = segs[0];

    return (rc);
}