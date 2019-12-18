#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_3__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct rdma_cqe_responder {scalar_t__ status; TYPE_1__ srq_wr_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  wr_cons_cnt; } ;
struct qlnxr_srq {TYPE_2__ hw_srq; } ;
struct qlnxr_qp {int /*<<< orphan*/  ibqp; int /*<<< orphan*/  id; struct qlnxr_srq* srq; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_cq {int dummy; } ;
struct ib_wc {void* wr_id; int /*<<< orphan*/ * qp; int /*<<< orphan*/  src_qp; scalar_t__ byte_len; scalar_t__ vendor_err; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 void* HILO_U64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ RDMA_CQE_RESP_STS_WORK_REQUEST_FLUSHED_ERR ; 
 int /*<<< orphan*/  __process_resp_one (struct qlnxr_dev*,struct qlnxr_qp*,struct qlnxr_cq*,struct ib_wc*,struct rdma_cqe_responder*,void*) ; 

__attribute__((used)) static int
process_resp_one_srq(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	struct qlnxr_cq *cq,
	struct ib_wc *wc,
	struct rdma_cqe_responder *resp)
{
	struct qlnxr_srq	*srq = qp->srq;
	u64			wr_id;
	qlnx_host_t		*ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");
 
	wr_id = HILO_U64(resp->srq_wr_id.hi, resp->srq_wr_id.lo);

	if (resp->status == RDMA_CQE_RESP_STS_WORK_REQUEST_FLUSHED_ERR) {
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->vendor_err = 0;
		wc->wr_id = wr_id;
		wc->byte_len = 0;
		wc->src_qp = qp->id;
		wc->qp = &qp->ibqp;
		wc->wr_id = wr_id;
	} else {
		__process_resp_one(dev, qp, cq, wc, resp, wr_id);
	}

	/* PBL is maintained in case of WR granularity.
	 * So increment WR consumer after consuming WR
	 */
	srq->hw_srq.wr_cons_cnt++;

	QL_DPRINT12(ha, "exit\n");
	return 1;
}