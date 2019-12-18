#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_12__ {scalar_t__ wqe_cons; size_t cons; int /*<<< orphan*/  pbl; } ;
struct qlnxr_qp {TYPE_6__ sq; TYPE_5__* wqe_wr_id; int /*<<< orphan*/  ibqp; int /*<<< orphan*/  id; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_cq {int dummy; } ;
struct ib_wc {int status; int opcode; int byte_len; int /*<<< orphan*/  wr_id; int /*<<< orphan*/ * qp; int /*<<< orphan*/  src_qp; scalar_t__ wc_flags; scalar_t__ vendor_err; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_11__ {int opcode; int bytes_len; int /*<<< orphan*/  wqe_size; TYPE_4__* frmr; TYPE_2__* mr; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  signaled; } ;
struct TYPE_9__ {int /*<<< orphan*/  completed; } ;
struct TYPE_10__ {TYPE_3__ info; } ;
struct TYPE_7__ {int /*<<< orphan*/  completed; } ;
struct TYPE_8__ {TYPE_1__ info; } ;

/* Variables and functions */
#define  IB_WC_COMP_SWAP 134 
#define  IB_WC_FAST_REG_MR 133 
#define  IB_WC_FETCH_ADD 132 
#define  IB_WC_RDMA_READ 131 
#define  IB_WC_RDMA_WRITE 130 
#define  IB_WC_REG_MR 129 
#define  IB_WC_SEND 128 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ecore_chain_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnxr_chk_if_fmr (struct qlnxr_qp*) ; 
 int /*<<< orphan*/  qlnxr_inc_sw_cons (TYPE_6__*) ; 

__attribute__((used)) static int
process_req(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	struct qlnxr_cq *cq,
	int num_entries,
	struct ib_wc *wc,
	u16 hw_cons,
	enum ib_wc_status status,
	int force)
{
	u16		cnt = 0;
	qlnx_host_t	*ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");
 
	while (num_entries && qp->sq.wqe_cons != hw_cons) {
		if (!qp->wqe_wr_id[qp->sq.cons].signaled && !force) {
			qlnxr_chk_if_fmr(qp);
			/* skip WC */
			goto next_cqe;
		}

		/* fill WC */
		wc->status = status;
		wc->vendor_err = 0;
		wc->wc_flags = 0;
		wc->src_qp = qp->id;
		wc->qp = &qp->ibqp;

		// common section
		wc->wr_id = qp->wqe_wr_id[qp->sq.cons].wr_id;
		wc->opcode = qp->wqe_wr_id[qp->sq.cons].opcode;

		switch (wc->opcode) {

		case IB_WC_RDMA_WRITE:

			wc->byte_len = qp->wqe_wr_id[qp->sq.cons].bytes_len;

			QL_DPRINT12(ha,
				"opcode = IB_WC_RDMA_WRITE bytes = %d\n",
				qp->wqe_wr_id[qp->sq.cons].bytes_len);
			break;

		case IB_WC_COMP_SWAP:
		case IB_WC_FETCH_ADD:
			wc->byte_len = 8;
			break;

#if __FreeBSD_version >= 1102000
		case IB_WC_REG_MR:
			qp->wqe_wr_id[qp->sq.cons].mr->info.completed++;
			break;
#else
		case IB_WC_FAST_REG_MR:
			qp->wqe_wr_id[qp->sq.cons].frmr->info.completed++;
			break;
#endif /* #if __FreeBSD_version >= 1102000 */

		case IB_WC_RDMA_READ:
		case IB_WC_SEND:

			QL_DPRINT12(ha, "opcode = 0x%x \n", wc->opcode);
			break;
		default:
			;//DP_ERR("TBD ERROR");
		}

		num_entries--;
		wc++;
		cnt++;
next_cqe:
		while (qp->wqe_wr_id[qp->sq.cons].wqe_size--)
			ecore_chain_consume(&qp->sq.pbl);
		qlnxr_inc_sw_cons(&qp->sq);
	}

	QL_DPRINT12(ha, "exit cnt = 0x%x\n", cnt);
	return cnt;
}