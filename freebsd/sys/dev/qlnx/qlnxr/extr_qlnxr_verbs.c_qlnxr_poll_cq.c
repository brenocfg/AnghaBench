#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct rdma_cqe_requester {int /*<<< orphan*/  flags; TYPE_2__ qp_handle; } ;
union rdma_cqe {int /*<<< orphan*/  resp; struct rdma_cqe_requester req; } ;
typedef  scalar_t__ u32 ;
struct qlnxr_qp {int /*<<< orphan*/  ibqp; } ;
struct qlnxr_dev {TYPE_5__* ha; } ;
struct TYPE_10__ {int /*<<< orphan*/  icid; } ;
struct TYPE_11__ {TYPE_3__ data; } ;
struct qlnxr_cq {scalar_t__ cq_type; int /*<<< orphan*/  cq_lock; TYPE_4__ db; int /*<<< orphan*/  arm_flags; scalar_t__ cq_cons; int /*<<< orphan*/  pbl; union rdma_cqe* latest_cqe; int /*<<< orphan*/  icid; scalar_t__ destroyed; } ;
struct ib_wc {int /*<<< orphan*/ * qp; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_12__ {TYPE_1__* ifp; } ;
typedef  TYPE_5__ qlnx_host_t ;
typedef  enum rdma_cqe_type { ____Placeholder_rdma_cqe_type } rdma_cqe_type ;
struct TYPE_8__ {int if_drv_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HILO_U64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ QLNXR_CQ_TYPE_GSI ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  RDMA_CQE_REQUESTER_TYPE ; 
#define  RDMA_CQE_TYPE_INVALID 131 
#define  RDMA_CQE_TYPE_REQUESTER 130 
#define  RDMA_CQE_TYPE_RESPONDER_RQ 129 
#define  RDMA_CQE_TYPE_RESPONDER_SRQ 128 
 int /*<<< orphan*/  doorbell_cq (struct qlnxr_dev*,struct qlnxr_cq*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_chain_get_cons_idx_u32 (int /*<<< orphan*/ *) ; 
 struct qlnxr_cq* get_qlnxr_cq (struct ib_cq*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_cqe (struct qlnxr_cq*,union rdma_cqe*) ; 
 int qlnxr_gsi_poll_cq (struct ib_cq*,int,struct ib_wc*) ; 
 int qlnxr_poll_cq_req (struct qlnxr_dev*,struct qlnxr_qp*,struct qlnxr_cq*,int,struct ib_wc*,struct rdma_cqe_requester*) ; 
 int qlnxr_poll_cq_resp (struct qlnxr_dev*,struct qlnxr_qp*,struct qlnxr_cq*,int,struct ib_wc*,int /*<<< orphan*/ *,int*) ; 
 int qlnxr_poll_cq_resp_srq (struct qlnxr_dev*,struct qlnxr_qp*,struct qlnxr_cq*,int,struct ib_wc*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_consume_req_cqe (struct qlnxr_cq*,struct qlnxr_qp*,struct rdma_cqe_requester*,int*) ; 

int
qlnxr_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct qlnxr_cq	*cq = get_qlnxr_cq(ibcq);
	struct qlnxr_dev *dev = get_qlnxr_dev((ibcq->device));
	int		done = 0;
	union rdma_cqe	*cqe = cq->latest_cqe;
	int 		update = 0;
	u32		old_cons, new_cons;
	unsigned long	flags;
	qlnx_host_t	*ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	if (!(ha->ifp->if_drv_flags & IFF_DRV_RUNNING))
		return -EINVAL;
 
	if (cq->destroyed) {
		QL_DPRINT11(ha, "called after destroy for cq %p (icid=%d)\n",
			cq, cq->icid);
		return 0;
	}

	if (cq->cq_type == QLNXR_CQ_TYPE_GSI)
		return qlnxr_gsi_poll_cq(ibcq, num_entries, wc);

	spin_lock_irqsave(&cq->cq_lock, flags);

	old_cons = ecore_chain_get_cons_idx_u32(&cq->pbl);

	while (num_entries && is_valid_cqe(cq, cqe)) {
		int cnt = 0;
		struct qlnxr_qp *qp;
		struct rdma_cqe_requester *resp_cqe;
		enum rdma_cqe_type cqe_type;

		/* prevent speculative reads of any field of CQE */
		rmb();

		resp_cqe = &cqe->req;
		qp = (struct qlnxr_qp *)(uintptr_t)HILO_U64(resp_cqe->qp_handle.hi,
						resp_cqe->qp_handle.lo);

		if (!qp) {
			QL_DPRINT11(ha, "qp = NULL\n");
			break;
		}

		wc->qp = &qp->ibqp;

		cqe_type = GET_FIELD(resp_cqe->flags, RDMA_CQE_REQUESTER_TYPE);

		switch (cqe_type) {
		case RDMA_CQE_TYPE_REQUESTER:
			cnt = qlnxr_poll_cq_req(dev, qp, cq, num_entries,
					wc, &cqe->req);
			try_consume_req_cqe(cq, qp, &cqe->req, &update);
			break;
		case RDMA_CQE_TYPE_RESPONDER_RQ:
			cnt = qlnxr_poll_cq_resp(dev, qp, cq, num_entries,
					wc, &cqe->resp, &update);
			break;
		case RDMA_CQE_TYPE_RESPONDER_SRQ:
			cnt = qlnxr_poll_cq_resp_srq(dev, qp, cq, num_entries,
					wc, &cqe->resp, &update);
			break;
		case RDMA_CQE_TYPE_INVALID:
		default:
			QL_DPRINT11(ha, "cqe type [0x%x] invalid\n", cqe_type);
			break;
		}
		num_entries -= cnt;
		wc += cnt;
		done += cnt;

		cqe = cq->latest_cqe;
	}
	new_cons = ecore_chain_get_cons_idx_u32(&cq->pbl);

	cq->cq_cons += new_cons - old_cons;

	if (update) {
		/* doorbell notifies abount latest VALID entry,
		 * but chain already point to the next INVALID one
		 */
		doorbell_cq(dev, cq, cq->cq_cons - 1, cq->arm_flags);
		QL_DPRINT12(ha, "cq = %p cons = 0x%x "
			"arm_flags = 0x%x db.icid = 0x%x\n", cq,
			(cq->cq_cons - 1), cq->arm_flags, cq->db.data.icid);
	}

	spin_unlock_irqrestore(&cq->cq_lock, flags);

	QL_DPRINT12(ha, "exit\n");
 
	return done;
}