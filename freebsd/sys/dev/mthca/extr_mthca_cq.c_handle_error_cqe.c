#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mthca_qp {int dummy; } ;
struct mthca_err_cqe {int syndrome; int my_qpn; int wqe; int /*<<< orphan*/  db_cnt; int /*<<< orphan*/  vendor_err; } ;
struct mthca_dev {int dummy; } ;
struct mthca_cq {int /*<<< orphan*/  cons_index; int /*<<< orphan*/  cqn; } ;
struct ib_wc {int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_BAD_RESP_ERR ; 
 int /*<<< orphan*/  IB_WC_GENERAL_ERR ; 
 int /*<<< orphan*/  IB_WC_INV_EECN_ERR ; 
 int /*<<< orphan*/  IB_WC_INV_EEC_STATE_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_EEC_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_LEN_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_PROT_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_RDD_VIOL_ERR ; 
 int /*<<< orphan*/  IB_WC_MW_BIND_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_ABORT_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_INV_RD_REQ_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_INV_REQ_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_RNR_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
#define  SYNDROME_BAD_RESP_ERR 145 
#define  SYNDROME_INVAL_EECN_ERR 144 
#define  SYNDROME_INVAL_EEC_STATE_ERR 143 
#define  SYNDROME_LOCAL_ACCESS_ERR 142 
#define  SYNDROME_LOCAL_EEC_OP_ERR 141 
#define  SYNDROME_LOCAL_LENGTH_ERR 140 
#define  SYNDROME_LOCAL_PROT_ERR 139 
#define  SYNDROME_LOCAL_QP_OP_ERR 138 
#define  SYNDROME_LOCAL_RDD_VIOL_ERR 137 
#define  SYNDROME_MW_BIND_ERR 136 
#define  SYNDROME_REMOTE_ABORTED_ERR 135 
#define  SYNDROME_REMOTE_ACCESS_ERR 134 
#define  SYNDROME_REMOTE_INVAL_RD_REQ_ERR 133 
#define  SYNDROME_REMOTE_INVAL_REQ_ERR 132 
#define  SYNDROME_REMOTE_OP_ERR 131 
#define  SYNDROME_RETRY_EXC_ERR 130 
#define  SYNDROME_RNR_RETRY_EXC_ERR 129 
#define  SYNDROME_WR_FLUSH_ERR 128 
 int /*<<< orphan*/  be16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  be32_to_cpu (int) ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dump_cqe (struct mthca_dev*,struct mthca_err_cqe*) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_err_wqe (struct mthca_dev*,struct mthca_qp*,int,int,int*,int*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 

__attribute__((used)) static void handle_error_cqe(struct mthca_dev *dev, struct mthca_cq *cq,
			     struct mthca_qp *qp, int wqe_index, int is_send,
			     struct mthca_err_cqe *cqe,
			     struct ib_wc *entry, int *free_cqe)
{
	int dbd;
	__be32 new_wqe;

	if (cqe->syndrome == SYNDROME_LOCAL_QP_OP_ERR) {
		mthca_dbg(dev, "local QP operation err "
			  "(QPN %06x, WQE @ %08x, CQN %06x, index %d)\n",
			  be32_to_cpu(cqe->my_qpn), be32_to_cpu(cqe->wqe),
			  cq->cqn, cq->cons_index);
		dump_cqe(dev, cqe);
	}

	/*
	 * For completions in error, only work request ID, status, vendor error
	 * (and freed resource count for RD) have to be set.
	 */
	switch (cqe->syndrome) {
	case SYNDROME_LOCAL_LENGTH_ERR:
		entry->status = IB_WC_LOC_LEN_ERR;
		break;
	case SYNDROME_LOCAL_QP_OP_ERR:
		entry->status = IB_WC_LOC_QP_OP_ERR;
		break;
	case SYNDROME_LOCAL_EEC_OP_ERR:
		entry->status = IB_WC_LOC_EEC_OP_ERR;
		break;
	case SYNDROME_LOCAL_PROT_ERR:
		entry->status = IB_WC_LOC_PROT_ERR;
		break;
	case SYNDROME_WR_FLUSH_ERR:
		entry->status = IB_WC_WR_FLUSH_ERR;
		break;
	case SYNDROME_MW_BIND_ERR:
		entry->status = IB_WC_MW_BIND_ERR;
		break;
	case SYNDROME_BAD_RESP_ERR:
		entry->status = IB_WC_BAD_RESP_ERR;
		break;
	case SYNDROME_LOCAL_ACCESS_ERR:
		entry->status = IB_WC_LOC_ACCESS_ERR;
		break;
	case SYNDROME_REMOTE_INVAL_REQ_ERR:
		entry->status = IB_WC_REM_INV_REQ_ERR;
		break;
	case SYNDROME_REMOTE_ACCESS_ERR:
		entry->status = IB_WC_REM_ACCESS_ERR;
		break;
	case SYNDROME_REMOTE_OP_ERR:
		entry->status = IB_WC_REM_OP_ERR;
		break;
	case SYNDROME_RETRY_EXC_ERR:
		entry->status = IB_WC_RETRY_EXC_ERR;
		break;
	case SYNDROME_RNR_RETRY_EXC_ERR:
		entry->status = IB_WC_RNR_RETRY_EXC_ERR;
		break;
	case SYNDROME_LOCAL_RDD_VIOL_ERR:
		entry->status = IB_WC_LOC_RDD_VIOL_ERR;
		break;
	case SYNDROME_REMOTE_INVAL_RD_REQ_ERR:
		entry->status = IB_WC_REM_INV_RD_REQ_ERR;
		break;
	case SYNDROME_REMOTE_ABORTED_ERR:
		entry->status = IB_WC_REM_ABORT_ERR;
		break;
	case SYNDROME_INVAL_EECN_ERR:
		entry->status = IB_WC_INV_EECN_ERR;
		break;
	case SYNDROME_INVAL_EEC_STATE_ERR:
		entry->status = IB_WC_INV_EEC_STATE_ERR;
		break;
	default:
		entry->status = IB_WC_GENERAL_ERR;
		break;
	}

	entry->vendor_err = cqe->vendor_err;

	/*
	 * Mem-free HCAs always generate one CQE per WQE, even in the
	 * error case, so we don't have to check the doorbell count, etc.
	 */
	if (mthca_is_memfree(dev))
		return;

	mthca_free_err_wqe(dev, qp, is_send, wqe_index, &dbd, &new_wqe);

	/*
	 * If we're at the end of the WQE chain, or we've used up our
	 * doorbell count, free the CQE.  Otherwise just update it for
	 * the next poll operation.
	 */
	if (!(new_wqe & cpu_to_be32(0x3f)) || (!cqe->db_cnt && dbd))
		return;

	be16_add_cpu(&cqe->db_cnt, -dbd);
	cqe->wqe      = new_wqe;
	cqe->syndrome = SYNDROME_WR_FLUSH_ERR;

	*free_cqe = 0;
}