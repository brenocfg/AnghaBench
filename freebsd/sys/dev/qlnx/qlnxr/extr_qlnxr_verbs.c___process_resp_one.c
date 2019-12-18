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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct rdma_cqe_responder {int flags; int /*<<< orphan*/  imm_data_or_inv_r_Key; int /*<<< orphan*/  length; int /*<<< orphan*/  status; } ;
struct qlnxr_qp {int /*<<< orphan*/  ibqp; int /*<<< orphan*/  id; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_cq {int /*<<< orphan*/  icid; } ;
struct TYPE_2__ {void* imm_data; } ;
struct ib_wc {int status; int /*<<< orphan*/  wr_id; int /*<<< orphan*/ * qp; int /*<<< orphan*/  src_qp; scalar_t__ vendor_err; scalar_t__ wc_flags; TYPE_1__ ex; void* opcode; void* byte_len; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_LOC_ACCESS_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_LOC_QP_OP_ERR ; 
 int IB_WC_MW_BIND_ERR ; 
 void* IB_WC_RECV ; 
 void* IB_WC_RECV_RDMA_WITH_IMM ; 
 int IB_WC_REM_INV_RD_REQ_ERR ; 
 int IB_WC_SUCCESS ; 
 scalar_t__ IB_WC_WITH_IMM ; 
 scalar_t__ IB_WC_WITH_INVALIDATE ; 
#define  QLNXR_RESP_IMM 137 
 int QLNXR_RESP_INV ; 
#define  QLNXR_RESP_RDMA 136 
#define  QLNXR_RESP_RDMA_IMM 135 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*,int,struct qlnxr_qp*,int /*<<< orphan*/ ,struct qlnxr_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
#define  RDMA_CQE_RESP_STS_LOCAL_ACCESS_ERR 134 
#define  RDMA_CQE_RESP_STS_LOCAL_LENGTH_ERR 133 
#define  RDMA_CQE_RESP_STS_LOCAL_PROTECTION_ERR 132 
#define  RDMA_CQE_RESP_STS_LOCAL_QP_OPERATION_ERR 131 
#define  RDMA_CQE_RESP_STS_MEMORY_MGT_OPERATION_ERR 130 
#define  RDMA_CQE_RESP_STS_OK 129 
#define  RDMA_CQE_RESP_STS_REMOTE_INVALID_REQUEST_ERR 128 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__process_resp_one(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	struct qlnxr_cq *cq,
	struct ib_wc *wc,
	struct rdma_cqe_responder *resp,
	u64 wr_id)
{
	enum ib_wc_status	wc_status = IB_WC_SUCCESS;
#if __FreeBSD_version < 1102000
	u8			flags;
#endif
	qlnx_host_t		*ha = dev->ha;

	QL_DPRINT12(ha, "enter qp = %p resp->status = 0x%x\n",
		qp, resp->status);
 
	wc->opcode = IB_WC_RECV;
	wc->wc_flags = 0;

	switch (resp->status) {

	case RDMA_CQE_RESP_STS_LOCAL_ACCESS_ERR:
		wc_status = IB_WC_LOC_ACCESS_ERR;
		break;

	case RDMA_CQE_RESP_STS_LOCAL_LENGTH_ERR:
		wc_status = IB_WC_LOC_LEN_ERR;
		break;

	case RDMA_CQE_RESP_STS_LOCAL_QP_OPERATION_ERR:
		wc_status = IB_WC_LOC_QP_OP_ERR;
		break;

	case RDMA_CQE_RESP_STS_LOCAL_PROTECTION_ERR:
		wc_status = IB_WC_LOC_PROT_ERR;
		break;

	case RDMA_CQE_RESP_STS_MEMORY_MGT_OPERATION_ERR:
		wc_status = IB_WC_MW_BIND_ERR;
		break;

	case RDMA_CQE_RESP_STS_REMOTE_INVALID_REQUEST_ERR:
		wc_status = IB_WC_REM_INV_RD_REQ_ERR;
		break;

	case RDMA_CQE_RESP_STS_OK:

#if __FreeBSD_version >= 1102000
		if (resp->flags & QLNXR_RESP_IMM) {
			wc->ex.imm_data =
				le32_to_cpu(resp->imm_data_or_inv_r_Key);
			wc->wc_flags |= IB_WC_WITH_IMM;

			if (resp->flags & QLNXR_RESP_RDMA)
				wc->opcode = IB_WC_RECV_RDMA_WITH_IMM;

			if (resp->flags & QLNXR_RESP_INV) {
				QL_DPRINT11(ha,
					"Invalid flags QLNXR_RESP_INV [0x%x]"
					"qp = %p qp->id = 0x%x cq = %p"
					" cq->icid = 0x%x\n",
					resp->flags, qp, qp->id, cq, cq->icid );
			}
		} else if (resp->flags & QLNXR_RESP_INV) {
			wc->ex.imm_data =
				le32_to_cpu(resp->imm_data_or_inv_r_Key);
			wc->wc_flags |= IB_WC_WITH_INVALIDATE;

			if (resp->flags & QLNXR_RESP_RDMA) {
				QL_DPRINT11(ha,
					"Invalid flags QLNXR_RESP_RDMA [0x%x]"
					"qp = %p qp->id = 0x%x cq = %p"
					" cq->icid = 0x%x\n",
					resp->flags, qp, qp->id, cq, cq->icid );
			}
		} else if (resp->flags & QLNXR_RESP_RDMA) {
			QL_DPRINT11(ha, "Invalid flags QLNXR_RESP_RDMA [0x%x]"
				"qp = %p qp->id = 0x%x cq = %p cq->icid = 0x%x\n",
				resp->flags, qp, qp->id, cq, cq->icid );
		}
#else
		wc_status = IB_WC_SUCCESS;
		wc->byte_len = le32_to_cpu(resp->length);

		flags = resp->flags & QLNXR_RESP_RDMA_IMM;

		switch (flags) {

		case QLNXR_RESP_RDMA_IMM:
			/* update opcode */
			wc->opcode = IB_WC_RECV_RDMA_WITH_IMM;
			/* fall to set imm data */
		case QLNXR_RESP_IMM:
			wc->ex.imm_data =
				le32_to_cpu(resp->imm_data_or_inv_r_Key);
			wc->wc_flags |= IB_WC_WITH_IMM;
			break;
		case QLNXR_RESP_RDMA:
			QL_DPRINT11(ha, "Invalid flags QLNXR_RESP_RDMA [0x%x]"
				"qp = %p qp->id = 0x%x cq = %p cq->icid = 0x%x\n",
				resp->flags, qp, qp->id, cq, cq->icid );
			break;
		default:
			/* valid configuration, but nothing todo here */
			;
		}
#endif /* #if __FreeBSD_version >= 1102000 */

		break;
	default:
		wc_status = IB_WC_GENERAL_ERR;
	}

	/* fill WC */
	wc->status = wc_status;
	wc->vendor_err = 0;
	wc->src_qp = qp->id;
	wc->qp = &qp->ibqp;
	wc->wr_id = wr_id;

	QL_DPRINT12(ha, "exit status = 0x%x\n", wc_status);

	return;
}