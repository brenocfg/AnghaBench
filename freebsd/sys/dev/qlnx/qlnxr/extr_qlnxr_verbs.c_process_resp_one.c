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
typedef  int /*<<< orphan*/  u64 ;
struct rdma_cqe_responder {int dummy; } ;
struct TYPE_4__ {size_t cons; int /*<<< orphan*/  pbl; } ;
struct qlnxr_qp {TYPE_2__ rq; TYPE_1__* rqe_wr_id; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_cq {int dummy; } ;
struct ib_wc {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_3__ {int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  __process_resp_one (struct qlnxr_dev*,struct qlnxr_qp*,struct qlnxr_cq*,struct ib_wc*,struct rdma_cqe_responder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_chain_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnxr_inc_sw_cons (TYPE_2__*) ; 

__attribute__((used)) static int
process_resp_one(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	struct qlnxr_cq *cq,
	struct ib_wc *wc,
	struct rdma_cqe_responder *resp)
{
	qlnx_host_t	*ha = dev->ha;
	u64		wr_id = qp->rqe_wr_id[qp->rq.cons].wr_id;

	QL_DPRINT12(ha, "enter\n");
 
	__process_resp_one(dev, qp, cq, wc, resp, wr_id);

	while (qp->rqe_wr_id[qp->rq.cons].wqe_size--)
		ecore_chain_consume(&qp->rq.pbl);
	qlnxr_inc_sw_cons(&qp->rq);

	QL_DPRINT12(ha, "exit\n");
	return 1;
}