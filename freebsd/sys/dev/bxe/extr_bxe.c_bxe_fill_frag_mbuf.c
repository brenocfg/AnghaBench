#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;
struct mbuf {int m_len; TYPE_4__ m_pkthdr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sgl; } ;
struct eth_end_agg_rx_cqe {TYPE_1__ sgl_or_raw_data; int /*<<< orphan*/  pkt_len; } ;
struct bxe_sw_tpa_info {int len_on_bd; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  mbuf_alloc_sge; } ;
struct bxe_fastpath {int /*<<< orphan*/  index; TYPE_3__ eth_q_stats; TYPE_2__* rx_sge_mbuf_chain; } ;
struct TYPE_6__ {struct mbuf* m; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,int,int,int,int,...) ; 
 int /*<<< orphan*/  DBG_LRO ; 
 int EINVAL ; 
 int PAGES_PER_SGE ; 
 int RX_SGE (int) ; 
 scalar_t__ SGE_PAGES ; 
 int bxe_alloc_rx_sge_mbuf (struct bxe_fastpath*,int) ; 
 int /*<<< orphan*/  bxe_panic (struct bxe_softc*,char*) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int min (int,int) ; 

__attribute__((used)) static int
bxe_fill_frag_mbuf(struct bxe_softc          *sc,
                   struct bxe_fastpath       *fp,
                   struct bxe_sw_tpa_info    *tpa_info,
                   uint16_t                  queue,
                   uint16_t                  pages,
                   struct mbuf               *m,
			       struct eth_end_agg_rx_cqe *cqe,
                   uint16_t                  cqe_idx)
{
    struct mbuf *m_frag;
    uint32_t frag_len, frag_size, i;
    uint16_t sge_idx;
    int rc = 0;
    int j;

    frag_size = le16toh(cqe->pkt_len) - tpa_info->len_on_bd;

    BLOGD(sc, DBG_LRO,
          "fp[%02d].tpa[%02d] TPA fill len_on_bd=%d frag_size=%d pages=%d\n",
          fp->index, queue, tpa_info->len_on_bd, frag_size, pages);

    /* make sure the aggregated frame is not too big to handle */
    if (pages > 8 * PAGES_PER_SGE) {

        uint32_t *tmp = (uint32_t *)cqe;

        BLOGE(sc, "fp[%02d].sge[0x%04x] has too many pages (%d)! "
                  "pkt_len=%d len_on_bd=%d frag_size=%d\n",
              fp->index, cqe_idx, pages, le16toh(cqe->pkt_len),
              tpa_info->len_on_bd, frag_size);

        BLOGE(sc, "cqe [0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x]\n",
            *tmp, *(tmp+1), *(tmp+2), *(tmp+3), *(tmp+4), *(tmp+5), *(tmp+6), *(tmp+7)); 

        bxe_panic(sc, ("sge page count error\n"));
        return (EINVAL);
    }

    /*
     * Scan through the scatter gather list pulling individual mbufs into a
     * single mbuf for the host stack.
     */
    for (i = 0, j = 0; i < pages; i += PAGES_PER_SGE, j++) {
        sge_idx = RX_SGE(le16toh(cqe->sgl_or_raw_data.sgl[j]));

        /*
         * Firmware gives the indices of the SGE as if the ring is an array
         * (meaning that the "next" element will consume 2 indices).
         */
        frag_len = min(frag_size, (uint32_t)(SGE_PAGES));

        BLOGD(sc, DBG_LRO, "fp[%02d].tpa[%02d] TPA fill i=%d j=%d "
                           "sge_idx=%d frag_size=%d frag_len=%d\n",
              fp->index, queue, i, j, sge_idx, frag_size, frag_len);

        m_frag = fp->rx_sge_mbuf_chain[sge_idx].m;

        /* allocate a new mbuf for the SGE */
        rc = bxe_alloc_rx_sge_mbuf(fp, sge_idx);
        if (rc) {
            /* Leave all remaining SGEs in the ring! */
            return (rc);
        }

        /* update the fragment length */
        m_frag->m_len = frag_len;

        /* concatenate the fragment to the head mbuf */
        m_cat(m, m_frag);
        fp->eth_q_stats.mbuf_alloc_sge--;

        /* update the TPA mbuf size and remaining fragment size */
        m->m_pkthdr.len += frag_len;
        frag_size -= frag_len;
    }

    BLOGD(sc, DBG_LRO,
          "fp[%02d].tpa[%02d] TPA fill done frag_size=%d\n",
          fp->index, queue, frag_size);

    return (rc);
}