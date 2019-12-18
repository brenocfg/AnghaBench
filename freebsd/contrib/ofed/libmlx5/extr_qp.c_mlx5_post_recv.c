#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wqe_data_seg {scalar_t__ addr; void* lkey; scalar_t__ byte_count; } ;
struct mlx5_rwqe_sig {int dummy; } ;
struct TYPE_6__ {int head; int wqe_cnt; int max_gs; int wqe_shift; int /*<<< orphan*/  lock; int /*<<< orphan*/ * wrid; } ;
struct mlx5_qp {int wq_sig; TYPE_3__ rq; void** db; TYPE_1__* ibv_qp; } ;
struct ibv_recv_wr {int num_sge; int /*<<< orphan*/  wr_id; TYPE_2__* sg_list; struct ibv_recv_wr* next; } ;
struct ibv_qp {scalar_t__ qp_type; scalar_t__ state; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
struct TYPE_4__ {int /*<<< orphan*/  recv_cq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IBV_QPS_RTR ; 
 scalar_t__ IBV_QPT_RAW_PACKET ; 
 int MLX5_INVALID_LKEY ; 
 size_t MLX5_RCV_DBR ; 
 struct mlx5_wqe_data_seg* get_recv_wqe (struct mlx5_qp*,int) ; 
 void* htobe32 (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct mlx5_rwqe_sig*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 
 int mlx5_wq_overflow (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_data_ptr_seg (struct mlx5_wqe_data_seg*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sig_seg (struct mlx5_qp*,struct mlx5_rwqe_sig*,int,int) ; 
 int /*<<< orphan*/  to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx5_qp* to_mqp (struct ibv_qp*) ; 
 int /*<<< orphan*/  udma_to_device_barrier () ; 
 scalar_t__ unlikely (int) ; 

int mlx5_post_recv(struct ibv_qp *ibqp, struct ibv_recv_wr *wr,
		   struct ibv_recv_wr **bad_wr)
{
	struct mlx5_qp *qp = to_mqp(ibqp);
	struct mlx5_wqe_data_seg *scat;
	int err = 0;
	int nreq;
	int ind;
	int i, j;
	struct mlx5_rwqe_sig *sig;

	mlx5_spin_lock(&qp->rq.lock);

	ind = qp->rq.head & (qp->rq.wqe_cnt - 1);

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		if (unlikely(mlx5_wq_overflow(&qp->rq, nreq,
					      to_mcq(qp->ibv_qp->recv_cq)))) {
			err = ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		if (unlikely(wr->num_sge > qp->rq.max_gs)) {
			err = EINVAL;
			*bad_wr = wr;
			goto out;
		}

		scat = get_recv_wqe(qp, ind);
		sig = (struct mlx5_rwqe_sig *)scat;
		if (unlikely(qp->wq_sig)) {
			memset(sig, 0, 1 << qp->rq.wqe_shift);
			++scat;
		}

		for (i = 0, j = 0; i < wr->num_sge; ++i) {
			if (unlikely(!wr->sg_list[i].length))
				continue;
			set_data_ptr_seg(scat + j++, wr->sg_list + i, 0);
		}

		if (j < qp->rq.max_gs) {
			scat[j].byte_count = 0;
			scat[j].lkey       = htobe32(MLX5_INVALID_LKEY);
			scat[j].addr       = 0;
		}

		if (unlikely(qp->wq_sig))
			set_sig_seg(qp, sig, (wr->num_sge + 1) << 4,
				    qp->rq.head & 0xffff);

		qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (qp->rq.wqe_cnt - 1);
	}

out:
	if (likely(nreq)) {
		qp->rq.head += nreq;

		/*
		 * Make sure that descriptors are written before
		 * doorbell record.
		 */
		udma_to_device_barrier();

		/*
		 * For Raw Packet QP, avoid updating the doorbell record
		 * as long as the QP isn't in RTR state, to avoid receiving
		 * packets in illegal states.
		 * This is only for Raw Packet QPs since they are represented
		 * differently in the hardware.
		 */
		if (likely(!(ibqp->qp_type == IBV_QPT_RAW_PACKET &&
			     ibqp->state < IBV_QPS_RTR)))
			qp->db[MLX5_RCV_DBR] = htobe32(qp->rq.head & 0xffff);
	}

	mlx5_spin_unlock(&qp->rq.lock);

	return err;
}