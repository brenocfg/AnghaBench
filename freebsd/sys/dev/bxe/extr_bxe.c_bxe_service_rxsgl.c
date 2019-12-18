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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct mbuf {size_t m_len; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sgl; } ;
struct eth_fast_path_rx_cqe {TYPE_3__ sgl_or_raw_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbuf_alloc_sge; } ;
struct bxe_fastpath {int /*<<< orphan*/  sc; TYPE_2__ eth_q_stats; TYPE_1__* rx_sge_mbuf_chain; } ;
struct TYPE_4__ {struct mbuf* m; } ;

/* Variables and functions */
 scalar_t__ PAGES_PER_SGE ; 
 size_t RX_SGE (int /*<<< orphan*/ ) ; 
 size_t SGE_PAGE_ALIGN (size_t) ; 
 size_t SGE_PAGE_SHIFT ; 
 scalar_t__ SGE_PAGE_SIZE ; 
 size_t bxe_alloc_rx_sge_mbuf (struct bxe_fastpath*,size_t) ; 
 int /*<<< orphan*/  bxe_update_sge_prod (int /*<<< orphan*/ ,struct bxe_fastpath*,size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static uint8_t
bxe_service_rxsgl(
                 struct bxe_fastpath *fp,
                 uint16_t len,
                 uint16_t lenonbd,
                 struct mbuf *m,
                 struct eth_fast_path_rx_cqe *cqe_fp)
{
    struct mbuf *m_frag;
    uint16_t frags, frag_len;
    uint16_t sge_idx = 0;
    uint16_t j;
    uint8_t i, rc = 0;
    uint32_t frag_size;

    /* adjust the mbuf */
    m->m_len = lenonbd;

    frag_size =  len - lenonbd;
    frags = SGE_PAGE_ALIGN(frag_size) >> SGE_PAGE_SHIFT;

    for (i = 0, j = 0; i < frags; i += PAGES_PER_SGE, j++) {
        sge_idx = RX_SGE(le16toh(cqe_fp->sgl_or_raw_data.sgl[j]));

        m_frag = fp->rx_sge_mbuf_chain[sge_idx].m;
        frag_len = min(frag_size, (uint32_t)(SGE_PAGE_SIZE));
        m_frag->m_len = frag_len;

       /* allocate a new mbuf for the SGE */
        rc = bxe_alloc_rx_sge_mbuf(fp, sge_idx);
        if (rc) {
            /* Leave all remaining SGEs in the ring! */
            return (rc);
        }
        fp->eth_q_stats.mbuf_alloc_sge--;

        /* concatenate the fragment to the head mbuf */
        m_cat(m, m_frag);

        frag_size -= frag_len;
    }

    bxe_update_sge_prod(fp->sc, fp, frags, &cqe_fp->sgl_or_raw_data);

    return rc;
}