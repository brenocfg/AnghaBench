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
struct qlnx_fastpath {int rss_id; scalar_t__ err_m_getjcl; scalar_t__ err_m_getcl; scalar_t__ rx_pkts; scalar_t__ err_tx_cons_idx_conflict; scalar_t__ err_tx_free_pkt_null; scalar_t__ err_tx_defrag; scalar_t__ err_tx_dmamap_load; scalar_t__ err_tx_non_tso_max_seg; scalar_t__ err_tx_defrag_dmamap_load; scalar_t__ err_tx_dmamap_create; scalar_t__ err_tx_nsegs_gt_elem_left; scalar_t__ tx_tso_min_nsegs; scalar_t__ tx_tso_max_nsegs; scalar_t__ tx_nsegs_gt_elem_left; scalar_t__ tx_defrag; scalar_t__ tx_lso_wnd_min_len; scalar_t__ tx_pkts_compl_intr; scalar_t__ tx_pkts_compl_fp; scalar_t__ tx_pkts_trans_fp; scalar_t__ tx_pkts_compl_ctx; scalar_t__ tx_pkts_trans_ctx; scalar_t__ tx_pkts_completed; scalar_t__ tx_pkts_transmitted; scalar_t__ tx_pkts_freed; scalar_t__ tx_pkts_processed; scalar_t__ tx_ring_full; int /*<<< orphan*/  name; TYPE_2__** txq; TYPE_1__* rxq; int /*<<< orphan*/ * sb_info; TYPE_3__* edev; } ;
struct TYPE_7__ {int num_rss; int num_tc; TYPE_2__* txq_array; TYPE_1__* rxq_array; int /*<<< orphan*/ * sb_array; struct qlnx_fastpath* fp_array; } ;
typedef  TYPE_3__ qlnx_host_t ;
struct TYPE_6__ {int index; } ;
struct TYPE_5__ {int rxq_id; } ;

/* Variables and functions */
 char* qlnx_name_str ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

__attribute__((used)) static void
qlnx_init_fp(qlnx_host_t *ha)
{
	int rss_id, txq_array_index, tc;

	for (rss_id = 0; rss_id < ha->num_rss; rss_id++) {

		struct qlnx_fastpath *fp = &ha->fp_array[rss_id];

		fp->rss_id = rss_id;
		fp->edev = ha;
		fp->sb_info = &ha->sb_array[rss_id];
		fp->rxq = &ha->rxq_array[rss_id];
		fp->rxq->rxq_id = rss_id;

		for (tc = 0; tc < ha->num_tc; tc++) {
                        txq_array_index = tc * ha->num_rss + rss_id;
                        fp->txq[tc] = &ha->txq_array[txq_array_index];
                        fp->txq[tc]->index = txq_array_index;
		}

		snprintf(fp->name, sizeof(fp->name), "%s-fp-%d", qlnx_name_str,
			rss_id);

		fp->tx_ring_full = 0;

		/* reset all the statistics counters */

		fp->tx_pkts_processed = 0;
		fp->tx_pkts_freed = 0;
		fp->tx_pkts_transmitted = 0;
		fp->tx_pkts_completed = 0;

#ifdef QLNX_TRACE_PERF_DATA
		fp->tx_pkts_trans_ctx = 0;
		fp->tx_pkts_compl_ctx = 0;
		fp->tx_pkts_trans_fp = 0;
		fp->tx_pkts_compl_fp = 0;
		fp->tx_pkts_compl_intr = 0;
#endif
		fp->tx_lso_wnd_min_len = 0;
		fp->tx_defrag = 0;
		fp->tx_nsegs_gt_elem_left = 0;
		fp->tx_tso_max_nsegs = 0;
		fp->tx_tso_min_nsegs = 0;
		fp->err_tx_nsegs_gt_elem_left = 0;
		fp->err_tx_dmamap_create = 0;
		fp->err_tx_defrag_dmamap_load = 0;
		fp->err_tx_non_tso_max_seg = 0;
		fp->err_tx_dmamap_load = 0;
		fp->err_tx_defrag = 0;
		fp->err_tx_free_pkt_null = 0;
		fp->err_tx_cons_idx_conflict = 0;

		fp->rx_pkts = 0;
		fp->err_m_getcl = 0;
		fp->err_m_getjcl = 0;
        }
	return;
}