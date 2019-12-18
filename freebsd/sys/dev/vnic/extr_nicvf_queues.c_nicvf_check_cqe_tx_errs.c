#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nicvf {int dummy; } ;
struct cqe_send_t {int send_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  csum_overflow; int /*<<< orphan*/  csum_overlap; int /*<<< orphan*/  mem_fault; int /*<<< orphan*/  tstmp_timeout; int /*<<< orphan*/  tstmp_conflict; int /*<<< orphan*/  data_fault; int /*<<< orphan*/  lock_viol; int /*<<< orphan*/  mem_seq_err; int /*<<< orphan*/  data_seq_err; int /*<<< orphan*/  imm_size_oflow; int /*<<< orphan*/  subdesc_err; int /*<<< orphan*/  hdr_cons_err; int /*<<< orphan*/  desc_fault; int /*<<< orphan*/  good; } ;
struct cmp_queue_stats {TYPE_1__ tx; } ;
struct cmp_queue {struct cmp_queue_stats stats; } ;

/* Variables and functions */
#define  CQ_TX_ERROP_CK_OFLOW 141 
#define  CQ_TX_ERROP_CK_OVERLAP 140 
#define  CQ_TX_ERROP_DATA_FAULT 139 
#define  CQ_TX_ERROP_DATA_SEQUENCE_ERR 138 
#define  CQ_TX_ERROP_DESC_FAULT 137 
#define  CQ_TX_ERROP_GOOD 136 
#define  CQ_TX_ERROP_HDR_CONS_ERR 135 
#define  CQ_TX_ERROP_IMM_SIZE_OFLOW 134 
#define  CQ_TX_ERROP_LOCK_VIOL 133 
#define  CQ_TX_ERROP_MEM_FAULT 132 
#define  CQ_TX_ERROP_MEM_SEQUENCE_ERR 131 
#define  CQ_TX_ERROP_SUBDC_ERR 130 
#define  CQ_TX_ERROP_TSTMP_CONFLICT 129 
#define  CQ_TX_ERROP_TSTMP_TIMEOUT 128 

int
nicvf_check_cqe_tx_errs(struct nicvf *nic, struct cmp_queue *cq,
    struct cqe_send_t *cqe_tx)
{
	struct cmp_queue_stats *stats = &cq->stats;

	switch (cqe_tx->send_status) {
	case CQ_TX_ERROP_GOOD:
		stats->tx.good++;
		return (0);
	case CQ_TX_ERROP_DESC_FAULT:
		stats->tx.desc_fault++;
		break;
	case CQ_TX_ERROP_HDR_CONS_ERR:
		stats->tx.hdr_cons_err++;
		break;
	case CQ_TX_ERROP_SUBDC_ERR:
		stats->tx.subdesc_err++;
		break;
	case CQ_TX_ERROP_IMM_SIZE_OFLOW:
		stats->tx.imm_size_oflow++;
		break;
	case CQ_TX_ERROP_DATA_SEQUENCE_ERR:
		stats->tx.data_seq_err++;
		break;
	case CQ_TX_ERROP_MEM_SEQUENCE_ERR:
		stats->tx.mem_seq_err++;
		break;
	case CQ_TX_ERROP_LOCK_VIOL:
		stats->tx.lock_viol++;
		break;
	case CQ_TX_ERROP_DATA_FAULT:
		stats->tx.data_fault++;
		break;
	case CQ_TX_ERROP_TSTMP_CONFLICT:
		stats->tx.tstmp_conflict++;
		break;
	case CQ_TX_ERROP_TSTMP_TIMEOUT:
		stats->tx.tstmp_timeout++;
		break;
	case CQ_TX_ERROP_MEM_FAULT:
		stats->tx.mem_fault++;
		break;
	case CQ_TX_ERROP_CK_OVERLAP:
		stats->tx.csum_overlap++;
		break;
	case CQ_TX_ERROP_CK_OFLOW:
		stats->tx.csum_overflow++;
		break;
	}

	return (1);
}