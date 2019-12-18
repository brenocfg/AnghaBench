#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct rdma_sq_send_wqe {int wqe_size; void* length; void* inv_key_or_imm_data; } ;
struct rdma_sq_rdma_wqe_2nd {int dummy; } ;
struct rdma_sq_rdma_wqe_1st {int wqe_size; void* length; int /*<<< orphan*/  imm_data; } ;
struct rdma_sq_local_inv_wqe {int prev_wqe_size; int /*<<< orphan*/  inv_l_key; int /*<<< orphan*/  req_type; } ;
struct rdma_sq_fmr_wqe_1st {int wqe_size; int prev_wqe_size; } ;
struct rdma_sq_common_wqe {int flags; int prev_wqe_size; void* req_type; } ;
struct rdma_sq_atomic_wqe {int prev_wqe_size; void* r_key; } ;
struct TYPE_15__ {int /*<<< orphan*/  value; } ;
struct TYPE_17__ {int /*<<< orphan*/  raw; TYPE_4__ data; } ;
struct TYPE_19__ {size_t prod; TYPE_6__ db_data; scalar_t__ db; int /*<<< orphan*/  pbl; } ;
struct qlnxr_qp {scalar_t__ qp_type; scalar_t__ state; int prev_wqe_size; int /*<<< orphan*/  q_lock; TYPE_8__ sq; TYPE_3__* wqe_wr_id; scalar_t__ signaled; int /*<<< orphan*/  icid; } ;
struct qlnxr_dev {TYPE_7__* ha; } ;
struct TYPE_13__ {int /*<<< orphan*/  invalidate_rkey; int /*<<< orphan*/  imm_data; } ;
struct ib_send_wr {int send_flags; int opcode; struct ib_send_wr* next; int /*<<< orphan*/  wr_id; TYPE_2__ ex; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_16__ {scalar_t__ doorbells; } ;
struct TYPE_18__ {int /*<<< orphan*/  pci_dbells; TYPE_5__ cdev; TYPE_1__* ifp; } ;
typedef  TYPE_7__ qlnx_host_t ;
struct TYPE_20__ {int /*<<< orphan*/  compare_add; int /*<<< orphan*/  swap; int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_14__ {int signaled; int wqe_size; int /*<<< orphan*/  wr_id; void* bytes_len; int /*<<< orphan*/  opcode; } ;
struct TYPE_12__ {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_READ ; 
 scalar_t__ ECORE_ROCE_QP_STATE_ERR ; 
 scalar_t__ ECORE_ROCE_QP_STATE_RTS ; 
 scalar_t__ ECORE_ROCE_QP_STATE_SQD ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IB_QPT_GSI ; 
 int IB_SEND_FENCE ; 
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_ATOMIC_CMP_AND_SWP 139 
#define  IB_WR_ATOMIC_FETCH_AND_ADD 138 
#define  IB_WR_FAST_REG_MR 137 
#define  IB_WR_LOCAL_INV 136 
#define  IB_WR_RDMA_READ 135 
#define  IB_WR_RDMA_READ_WITH_INV 134 
#define  IB_WR_RDMA_WRITE 133 
#define  IB_WR_RDMA_WRITE_WITH_IMM 132 
#define  IB_WR_REG_MR 131 
#define  IB_WR_SEND 130 
#define  IB_WR_SEND_WITH_IMM 129 
#define  IB_WR_SEND_WITH_INV 128 
 int IFF_DRV_RUNNING ; 
 scalar_t__ QLNX_IS_ROCE (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_7__*,char*,...) ; 
 void* RDMA_SQ_REQ_TYPE_ATOMIC_ADD ; 
 void* RDMA_SQ_REQ_TYPE_ATOMIC_CMP_AND_SWAP ; 
 void* RDMA_SQ_REQ_TYPE_FAST_MR ; 
 int /*<<< orphan*/  RDMA_SQ_REQ_TYPE_LOCAL_INVALIDATE ; 
 void* RDMA_SQ_REQ_TYPE_RDMA_RD ; 
 void* RDMA_SQ_REQ_TYPE_RDMA_WR ; 
 void* RDMA_SQ_REQ_TYPE_RDMA_WR_WITH_IMM ; 
 void* RDMA_SQ_REQ_TYPE_SEND ; 
 void* RDMA_SQ_REQ_TYPE_SEND_WITH_IMM ; 
 void* RDMA_SQ_REQ_TYPE_SEND_WITH_INVALIDATE ; 
 int /*<<< orphan*/  RDMA_SQ_SEND_WQE_COMP_FLG ; 
 int RDMA_SQ_SEND_WQE_COMP_FLG_MASK ; 
 int RDMA_SQ_SEND_WQE_COMP_FLG_SHIFT ; 
 int /*<<< orphan*/  RDMA_SQ_SEND_WQE_RD_FENCE_FLG ; 
 int /*<<< orphan*/  RDMA_SQ_SEND_WQE_SE_FLG ; 
 int /*<<< orphan*/  SET_FIELD2 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPEPTR_ADDR_SET (struct rdma_sq_atomic_wqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__* atomic_wr (struct ib_send_wr*) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_data ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct rdma_sq_common_wqe* ecore_chain_produce (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_chain_set_prod (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rdma_sq_common_wqe*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_qp* get_qlnxr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  htonl (void*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  qlnxr_can_post_send (struct qlnxr_qp*,struct ib_send_wr*) ; 
 int qlnxr_gsi_post_send (struct ib_qp*,struct ib_send_wr*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  qlnxr_ib_to_wc_opcode (int) ; 
 int /*<<< orphan*/  qlnxr_inc_sw_prod (TYPE_8__*) ; 
 int qlnxr_prepare_fmr (struct qlnxr_qp*,struct rdma_sq_fmr_wqe_1st*,struct ib_send_wr*) ; 
 int qlnxr_prepare_reg (struct qlnxr_qp*,struct rdma_sq_fmr_wqe_1st*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_prepare_sq_rdma_data (struct qlnxr_dev*,struct qlnxr_qp*,struct rdma_sq_rdma_wqe_1st*,struct rdma_sq_rdma_wqe_2nd*,struct ib_send_wr*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  qlnxr_prepare_sq_send_data (struct qlnxr_dev*,struct qlnxr_qp*,struct rdma_sq_send_wqe*,struct rdma_sq_send_wqe*,struct ib_send_wr*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  qlnxr_prepare_sq_sges (struct qlnxr_dev*,struct qlnxr_qp*,int /*<<< orphan*/ *,struct ib_send_wr*) ; 
 int /*<<< orphan*/  reg_wr (struct ib_send_wr*) ; 
 int /*<<< orphan*/  remote_va ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  swap_data ; 
 int /*<<< orphan*/  wmb () ; 

int
qlnxr_post_send(struct ib_qp *ibqp,
	struct ib_send_wr *wr,
	struct ib_send_wr **bad_wr)
{
	struct qlnxr_dev	*dev = get_qlnxr_dev(ibqp->device);
	struct qlnxr_qp		*qp = get_qlnxr_qp(ibqp);
	unsigned long 		flags;
	int 			status = 0, rc = 0;
	bool			comp;
	qlnx_host_t		*ha;
	uint32_t		reg_addr;
 
	*bad_wr = NULL;
	ha = dev->ha;

	QL_DPRINT12(ha, "exit[ibqp, wr, bad_wr] = [%p, %p, %p]\n",
		ibqp, wr, bad_wr);

	if (!(ha->ifp->if_drv_flags & IFF_DRV_RUNNING))
		return -EINVAL;

	if (qp->qp_type == IB_QPT_GSI)
		return qlnxr_gsi_post_send(ibqp, wr, bad_wr);

	spin_lock_irqsave(&qp->q_lock, flags);

	if (QLNX_IS_ROCE(dev) && (qp->state != ECORE_ROCE_QP_STATE_RTS) &&
	    (qp->state != ECORE_ROCE_QP_STATE_ERR) &&
	    (qp->state != ECORE_ROCE_QP_STATE_SQD)) {
		spin_unlock_irqrestore(&qp->q_lock, flags);
		*bad_wr = wr;
		QL_DPRINT11(ha, "QP in wrong state! QP icid=0x%x state %d\n",
			qp->icid, qp->state);
		return -EINVAL;
	}

	if (!wr) {
		QL_DPRINT11(ha, "Got an empty post send???\n");
	}

	while (wr) {
		struct rdma_sq_common_wqe	*wqe;
		struct rdma_sq_send_wqe		*swqe;
		struct rdma_sq_send_wqe		*swqe2;
		struct rdma_sq_rdma_wqe_1st	*rwqe;
		struct rdma_sq_rdma_wqe_2nd	*rwqe2;
		struct rdma_sq_local_inv_wqe	*iwqe;
		struct rdma_sq_atomic_wqe	*awqe1;
		struct rdma_sq_atomic_wqe	*awqe2;
		struct rdma_sq_atomic_wqe	*awqe3;
		struct rdma_sq_fmr_wqe_1st	*fwqe1;

		if (!qlnxr_can_post_send(qp, wr)) {
			status = -ENOMEM;
			*bad_wr = wr;
			break;
		}

		wqe = ecore_chain_produce(&qp->sq.pbl);

		qp->wqe_wr_id[qp->sq.prod].signaled =
			!!(wr->send_flags & IB_SEND_SIGNALED) || qp->signaled;

		/* common fields */
		wqe->flags = 0;
		wqe->flags |= (RDMA_SQ_SEND_WQE_COMP_FLG_MASK <<
				RDMA_SQ_SEND_WQE_COMP_FLG_SHIFT);

		SET_FIELD2(wqe->flags, RDMA_SQ_SEND_WQE_SE_FLG, \
			!!(wr->send_flags & IB_SEND_SOLICITED));

		comp = (!!(wr->send_flags & IB_SEND_SIGNALED)) ||
				(qp->signaled);

		SET_FIELD2(wqe->flags, RDMA_SQ_SEND_WQE_COMP_FLG, comp);
		SET_FIELD2(wqe->flags, RDMA_SQ_SEND_WQE_RD_FENCE_FLG,  \
			!!(wr->send_flags & IB_SEND_FENCE));

		wqe->prev_wqe_size = qp->prev_wqe_size;

		qp->wqe_wr_id[qp->sq.prod].opcode = qlnxr_ib_to_wc_opcode(wr->opcode);


		switch (wr->opcode) {

		case IB_WR_SEND_WITH_IMM:

			wqe->req_type = RDMA_SQ_REQ_TYPE_SEND_WITH_IMM;
			swqe = (struct rdma_sq_send_wqe *)wqe;
			swqe->wqe_size = 2;
			swqe2 = (struct rdma_sq_send_wqe *)
					ecore_chain_produce(&qp->sq.pbl);
			swqe->inv_key_or_imm_data =
				cpu_to_le32(wr->ex.imm_data);
			swqe->length = cpu_to_le32(
						qlnxr_prepare_sq_send_data(dev,
							qp, swqe, swqe2, wr,
							bad_wr));

			qp->wqe_wr_id[qp->sq.prod].wqe_size = swqe->wqe_size;
			qp->prev_wqe_size = swqe->wqe_size;
			qp->wqe_wr_id[qp->sq.prod].bytes_len = swqe->length;

			QL_DPRINT12(ha, "SEND w/ IMM length = %d imm data=%x\n",
				swqe->length, wr->ex.imm_data);

			break;

		case IB_WR_SEND:

			wqe->req_type = RDMA_SQ_REQ_TYPE_SEND;
			swqe = (struct rdma_sq_send_wqe *)wqe;

			swqe->wqe_size = 2;
			swqe2 = (struct rdma_sq_send_wqe *)
					ecore_chain_produce(&qp->sq.pbl);
			swqe->length = cpu_to_le32(
						qlnxr_prepare_sq_send_data(dev,
							qp, swqe, swqe2, wr,
							bad_wr));
			qp->wqe_wr_id[qp->sq.prod].wqe_size = swqe->wqe_size;
			qp->prev_wqe_size = swqe->wqe_size;
			qp->wqe_wr_id[qp->sq.prod].bytes_len = swqe->length;

			QL_DPRINT12(ha, "SEND w/o IMM length = %d\n",
				swqe->length);

			break;

		case IB_WR_SEND_WITH_INV:

			wqe->req_type = RDMA_SQ_REQ_TYPE_SEND_WITH_INVALIDATE;
			swqe = (struct rdma_sq_send_wqe *)wqe;
			swqe2 = (struct rdma_sq_send_wqe *)
					ecore_chain_produce(&qp->sq.pbl);
			swqe->wqe_size = 2;
			swqe->inv_key_or_imm_data =
				cpu_to_le32(wr->ex.invalidate_rkey);
			swqe->length = cpu_to_le32(qlnxr_prepare_sq_send_data(dev,
						qp, swqe, swqe2, wr, bad_wr));
			qp->wqe_wr_id[qp->sq.prod].wqe_size = swqe->wqe_size;
			qp->prev_wqe_size = swqe->wqe_size;
			qp->wqe_wr_id[qp->sq.prod].bytes_len = swqe->length;

			QL_DPRINT12(ha, "SEND w INVALIDATE length = %d\n",
				swqe->length);
			break;

		case IB_WR_RDMA_WRITE_WITH_IMM:

			wqe->req_type = RDMA_SQ_REQ_TYPE_RDMA_WR_WITH_IMM;
			rwqe = (struct rdma_sq_rdma_wqe_1st *)wqe;

			rwqe->wqe_size = 2;
			rwqe->imm_data = htonl(cpu_to_le32(wr->ex.imm_data));
			rwqe2 = (struct rdma_sq_rdma_wqe_2nd *)
					ecore_chain_produce(&qp->sq.pbl);
			rwqe->length = cpu_to_le32(qlnxr_prepare_sq_rdma_data(dev,
						qp, rwqe, rwqe2, wr, bad_wr));
			qp->wqe_wr_id[qp->sq.prod].wqe_size = rwqe->wqe_size;
			qp->prev_wqe_size = rwqe->wqe_size;
			qp->wqe_wr_id[qp->sq.prod].bytes_len = rwqe->length;

			QL_DPRINT12(ha,
				"RDMA WRITE w/ IMM length = %d imm data=%x\n",
				rwqe->length, rwqe->imm_data);

			break;

		case IB_WR_RDMA_WRITE:

			wqe->req_type = RDMA_SQ_REQ_TYPE_RDMA_WR;
			rwqe = (struct rdma_sq_rdma_wqe_1st *)wqe;

			rwqe->wqe_size = 2;
			rwqe2 = (struct rdma_sq_rdma_wqe_2nd *)
					ecore_chain_produce(&qp->sq.pbl);
			rwqe->length = cpu_to_le32(qlnxr_prepare_sq_rdma_data(dev,
						qp, rwqe, rwqe2, wr, bad_wr));
			qp->wqe_wr_id[qp->sq.prod].wqe_size = rwqe->wqe_size;
			qp->prev_wqe_size = rwqe->wqe_size;
			qp->wqe_wr_id[qp->sq.prod].bytes_len = rwqe->length;

			QL_DPRINT12(ha,
				"RDMA WRITE w/o IMM length = %d\n",
				rwqe->length);

			break;

		case IB_WR_RDMA_READ_WITH_INV:

			QL_DPRINT12(ha,
				"RDMA READ WITH INVALIDATE not supported\n");

			*bad_wr = wr;
			rc = -EINVAL;

			break;

		case IB_WR_RDMA_READ:

			wqe->req_type = RDMA_SQ_REQ_TYPE_RDMA_RD;
			rwqe = (struct rdma_sq_rdma_wqe_1st *)wqe;

			rwqe->wqe_size = 2;
			rwqe2 = (struct rdma_sq_rdma_wqe_2nd *)
					ecore_chain_produce(&qp->sq.pbl);
			rwqe->length = cpu_to_le32(qlnxr_prepare_sq_rdma_data(dev,
						qp, rwqe, rwqe2, wr, bad_wr));

			qp->wqe_wr_id[qp->sq.prod].wqe_size = rwqe->wqe_size;
			qp->prev_wqe_size = rwqe->wqe_size;
			qp->wqe_wr_id[qp->sq.prod].bytes_len = rwqe->length;

			QL_DPRINT12(ha, "RDMA READ length = %d\n",
				rwqe->length);

			break;

		case IB_WR_ATOMIC_CMP_AND_SWP:
		case IB_WR_ATOMIC_FETCH_AND_ADD:

			QL_DPRINT12(ha,
				"ATOMIC operation = %s\n",
				((wr->opcode == IB_WR_ATOMIC_CMP_AND_SWP) ?
					"IB_WR_ATOMIC_CMP_AND_SWP" : 
					"IB_WR_ATOMIC_FETCH_AND_ADD"));

			awqe1 = (struct rdma_sq_atomic_wqe *)wqe;
			awqe1->prev_wqe_size = 4;

			awqe2 = (struct rdma_sq_atomic_wqe *)
					ecore_chain_produce(&qp->sq.pbl);

			TYPEPTR_ADDR_SET(awqe2, remote_va, \
				atomic_wr(wr)->remote_addr);

			awqe2->r_key = cpu_to_le32(atomic_wr(wr)->rkey);

			awqe3 = (struct rdma_sq_atomic_wqe *)
					ecore_chain_produce(&qp->sq.pbl);

			if (wr->opcode == IB_WR_ATOMIC_FETCH_AND_ADD) {
				wqe->req_type = RDMA_SQ_REQ_TYPE_ATOMIC_ADD;
				TYPEPTR_ADDR_SET(awqe3, swap_data,
						 atomic_wr(wr)->compare_add);
			} else {
				wqe->req_type = RDMA_SQ_REQ_TYPE_ATOMIC_CMP_AND_SWAP;
				TYPEPTR_ADDR_SET(awqe3, swap_data,
						 atomic_wr(wr)->swap);
				TYPEPTR_ADDR_SET(awqe3, cmp_data,
						 atomic_wr(wr)->compare_add);
			}

			qlnxr_prepare_sq_sges(dev, qp, NULL, wr);

			qp->wqe_wr_id[qp->sq.prod].wqe_size = awqe1->prev_wqe_size;
			qp->prev_wqe_size = awqe1->prev_wqe_size;

			break;

		case IB_WR_LOCAL_INV:

			QL_DPRINT12(ha,
				"INVALIDATE length (IB_WR_LOCAL_INV)\n");

			iwqe = (struct rdma_sq_local_inv_wqe *)wqe;
			iwqe->prev_wqe_size = 1;

			iwqe->req_type = RDMA_SQ_REQ_TYPE_LOCAL_INVALIDATE;
			iwqe->inv_l_key = wr->ex.invalidate_rkey;
			qp->wqe_wr_id[qp->sq.prod].wqe_size = iwqe->prev_wqe_size;
			qp->prev_wqe_size = iwqe->prev_wqe_size;

			break;

#if __FreeBSD_version >= 1102000

		case IB_WR_REG_MR:

			QL_DPRINT12(ha, "IB_WR_REG_MR\n");

			wqe->req_type = RDMA_SQ_REQ_TYPE_FAST_MR;
			fwqe1 = (struct rdma_sq_fmr_wqe_1st *)wqe;
			fwqe1->wqe_size = 2;

			rc = qlnxr_prepare_reg(qp, fwqe1, reg_wr(wr));
			if (rc) {
				QL_DPRINT11(ha, "IB_WR_REG_MR failed rc=%d\n", rc);
				*bad_wr = wr;
				break;
			}

			qp->wqe_wr_id[qp->sq.prod].wqe_size = fwqe1->wqe_size;
			qp->prev_wqe_size = fwqe1->wqe_size;

			break;
#else
		case IB_WR_FAST_REG_MR:

			QL_DPRINT12(ha, "FAST_MR (IB_WR_FAST_REG_MR)\n");

			wqe->req_type = RDMA_SQ_REQ_TYPE_FAST_MR;
			fwqe1 = (struct rdma_sq_fmr_wqe_1st *)wqe;
			fwqe1->prev_wqe_size = 3;

			rc = qlnxr_prepare_fmr(qp, fwqe1, wr);

			if (rc) {
				QL_DPRINT12(ha,
					"FAST_MR (IB_WR_FAST_REG_MR) failed"
					" rc = %d\n", rc);
				*bad_wr = wr;
				break;
			}

			qp->wqe_wr_id[qp->sq.prod].wqe_size = fwqe1->prev_wqe_size;
			qp->prev_wqe_size = fwqe1->prev_wqe_size;

			break;
#endif /* #if __FreeBSD_version >= 1102000 */

		default:

			QL_DPRINT12(ha, "Invalid Opcode 0x%x!\n", wr->opcode);

			rc = -EINVAL;
			*bad_wr = wr;
			break;
		}

		if (*bad_wr) {
			/*
			 * restore prod to its position before this WR was processed
			 */
			ecore_chain_set_prod(&qp->sq.pbl,
			     le16_to_cpu(qp->sq.db_data.data.value),
			     wqe);
			/* restore prev_wqe_size */
			qp->prev_wqe_size = wqe->prev_wqe_size;
			status = rc;

			QL_DPRINT12(ha, "failed *bad_wr = %p\n", *bad_wr);
			break; /* out of the loop */
		}

		qp->wqe_wr_id[qp->sq.prod].wr_id = wr->wr_id;

		qlnxr_inc_sw_prod(&qp->sq);

		qp->sq.db_data.data.value++;

		wr = wr->next;
	}

	/* Trigger doorbell
	 * If there was a failure in the first WR then it will be triggered in
	 * vane. However this is not harmful (as long as the producer value is
	 * unchanged). For performance reasons we avoid checking for this
	 * redundant doorbell.
	 */
	wmb();
	//writel(qp->sq.db_data.raw, qp->sq.db);

	reg_addr = (uint32_t)((uint8_t *)qp->sq.db - (uint8_t *)ha->cdev.doorbells);
        bus_write_4(ha->pci_dbells, reg_addr, qp->sq.db_data.raw);
        bus_barrier(ha->pci_dbells,  0, 0, BUS_SPACE_BARRIER_READ);

	mmiowb();

	spin_unlock_irqrestore(&qp->q_lock, flags);

	QL_DPRINT12(ha, "exit[ibqp, wr, bad_wr] = [%p, %p, %p]\n",
		ibqp, wr, bad_wr);

	return status;
}