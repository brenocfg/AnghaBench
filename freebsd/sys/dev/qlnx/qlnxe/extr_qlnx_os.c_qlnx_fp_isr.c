#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct qlnx_tx_queue {int /*<<< orphan*/  tx_pbl; } ;
struct qlnx_fastpath {int tx_pkts_completed; int tx_pkts_compl_intr; int rx_pkts; int /*<<< orphan*/  sb_info; int /*<<< orphan*/  lro_cnt_64; int /*<<< orphan*/  lro_cnt_128; int /*<<< orphan*/  lro_cnt_256; int /*<<< orphan*/  lro_cnt_512; int /*<<< orphan*/  lro_cnt_1024; TYPE_2__* rxq; int /*<<< orphan*/  tx_mtx; int /*<<< orphan*/ * tx_comInt; struct qlnx_tx_queue** txq; } ;
struct lro_entry {int dummy; } ;
struct lro_ctrl {int lro_mbuf_count; int /*<<< orphan*/  lro_active; } ;
struct TYPE_10__ {int rss_idx; TYPE_4__* ha; } ;
typedef  TYPE_3__ qlnx_ivec_t ;
struct TYPE_11__ {scalar_t__ state; int num_rss; int num_tc; int /*<<< orphan*/  rx_pkt_threshold; TYPE_1__* ifp; int /*<<< orphan*/  err_fp_null; struct qlnx_fastpath* fp_array; int /*<<< orphan*/  err_illegal_intr; } ;
typedef  TYPE_4__ qlnx_host_t ;
struct TYPE_9__ {struct lro_ctrl lro; } ;
struct TYPE_8__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_LRO ; 
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 scalar_t__ QLNX_STATE_OPEN ; 
 int QLNX_TX_ELEM_THRESH ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct lro_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_chain_get_elem_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_sb_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_sb_update_sb_idx (int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int qlnx_rx_int (TYPE_4__*,struct qlnx_fastpath*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlnx_tx_int (TYPE_4__*,struct qlnx_fastpath*,struct qlnx_tx_queue*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  tcp_lro_flush (struct lro_ctrl*,struct lro_entry*) ; 
 int /*<<< orphan*/  tcp_lro_flush_all (struct lro_ctrl*) ; 
 int tx_compl ; 

__attribute__((used)) static void
qlnx_fp_isr(void *arg)
{
        qlnx_ivec_t		*ivec = arg;
        qlnx_host_t		*ha;
        struct qlnx_fastpath	*fp = NULL;
        int			idx;

        ha = ivec->ha;

        if (ha->state != QLNX_STATE_OPEN) {
                return;
        }

        idx = ivec->rss_idx;

        if ((idx = ivec->rss_idx) >= ha->num_rss) {
                QL_DPRINT1(ha, "illegal interrupt[%d]\n", idx);
                ha->err_illegal_intr++;
                return;
        }
        fp = &ha->fp_array[idx];

        if (fp == NULL) {
                ha->err_fp_null++;
        } else {
		int			rx_int = 0, total_rx_count = 0;
		int 			lro_enable, tc;
		struct qlnx_tx_queue	*txq;
		uint16_t		elem_left;

		lro_enable = ha->ifp->if_capenable & IFCAP_LRO;

                ecore_sb_ack(fp->sb_info, IGU_INT_DISABLE, 0);

                do {
                        for (tc = 0; tc < ha->num_tc; tc++) {

				txq = fp->txq[tc];

				if((int)(elem_left =
					ecore_chain_get_elem_left(&txq->tx_pbl)) <
						QLNX_TX_ELEM_THRESH)  {

                                	if (mtx_trylock(&fp->tx_mtx)) {
#ifdef QLNX_TRACE_PERF_DATA
						tx_compl = fp->tx_pkts_completed;
#endif

						qlnx_tx_int(ha, fp, fp->txq[tc]);
#ifdef QLNX_TRACE_PERF_DATA
						fp->tx_pkts_compl_intr +=
							(fp->tx_pkts_completed - tx_compl);
						if ((fp->tx_pkts_completed - tx_compl) <= 32)
							fp->tx_comInt[0]++;
						else if (((fp->tx_pkts_completed - tx_compl) > 32) &&
							((fp->tx_pkts_completed - tx_compl) <= 64))
							fp->tx_comInt[1]++;
						else if(((fp->tx_pkts_completed - tx_compl) > 64) &&
							((fp->tx_pkts_completed - tx_compl) <= 128))
							fp->tx_comInt[2]++;
						else if(((fp->tx_pkts_completed - tx_compl) > 128))
							fp->tx_comInt[3]++;
#endif
						mtx_unlock(&fp->tx_mtx);
					}
				}
                        }

                        rx_int = qlnx_rx_int(ha, fp, ha->rx_pkt_threshold,
                                        lro_enable);

                        if (rx_int) {
                                fp->rx_pkts += rx_int;
                                total_rx_count += rx_int;
                        }

                } while (rx_int);

#ifdef QLNX_SOFT_LRO
                {
                        struct lro_ctrl *lro;

                        lro = &fp->rxq->lro;

                        if (lro_enable && total_rx_count) {

#if (__FreeBSD_version >= 1100101) || (defined QLNX_QSORT_LRO)

#ifdef QLNX_TRACE_LRO_CNT
                                if (lro->lro_mbuf_count & ~1023)
                                        fp->lro_cnt_1024++;
                                else if (lro->lro_mbuf_count & ~511)
                                        fp->lro_cnt_512++;
                                else if (lro->lro_mbuf_count & ~255)
                                        fp->lro_cnt_256++;
                                else if (lro->lro_mbuf_count & ~127)
                                        fp->lro_cnt_128++;
                                else if (lro->lro_mbuf_count & ~63)
                                        fp->lro_cnt_64++;
#endif /* #ifdef QLNX_TRACE_LRO_CNT */

                                tcp_lro_flush_all(lro);

#else
                                struct lro_entry *queued;

                                while ((!SLIST_EMPTY(&lro->lro_active))) {
                                        queued = SLIST_FIRST(&lro->lro_active);
                                        SLIST_REMOVE_HEAD(&lro->lro_active, \
                                                next);
                                        tcp_lro_flush(lro, queued);
                                }
#endif /* #if (__FreeBSD_version >= 1100101) || (defined QLNX_QSORT_LRO) */
                        }
                }
#endif /* #ifdef QLNX_SOFT_LRO */

                ecore_sb_update_sb_idx(fp->sb_info);
                rmb();
                ecore_sb_ack(fp->sb_info, IGU_INT_ENABLE, 1);
        }

        return;
}