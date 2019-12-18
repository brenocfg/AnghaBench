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
struct TYPE_6__ {int head; int wqe_cnt; int max_gs; int /*<<< orphan*/  lock; int /*<<< orphan*/ * wrid; } ;
struct TYPE_5__ {void** db; } ;
struct TYPE_4__ {int /*<<< orphan*/  recv_cq; } ;
struct mlx5_ib_qp {TYPE_3__ rq; TYPE_2__ db; scalar_t__ wq_sig; TYPE_1__ ibqp; } ;
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {scalar_t__ state; } ;
struct ib_recv_wr {int num_sge; int /*<<< orphan*/  wr_id; scalar_t__ sg_list; struct ib_recv_wr* next; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int MLX5_INVALID_LKEY ; 
 void* cpu_to_be32 (int) ; 
 struct mlx5_wqe_data_seg* get_recv_wqe (struct mlx5_ib_qp*,int) ; 
 scalar_t__ likely (int) ; 
 int mlx5_ib_gsi_post_recv (struct ib_qp*,struct ib_recv_wr*,struct ib_recv_wr**) ; 
 scalar_t__ mlx5_wq_overflow (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_data_ptr_seg (struct mlx5_wqe_data_seg*,scalar_t__) ; 
 int /*<<< orphan*/  set_sig_seg (struct mlx5_rwqe_sig*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_qp* to_mqp (struct ib_qp*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

int mlx5_ib_post_recv(struct ib_qp *ibqp, struct ib_recv_wr *wr,
		      struct ib_recv_wr **bad_wr)
{
	struct mlx5_ib_qp *qp = to_mqp(ibqp);
	struct mlx5_wqe_data_seg *scat;
	struct mlx5_rwqe_sig *sig;
	struct mlx5_ib_dev *dev = to_mdev(ibqp->device);
	struct mlx5_core_dev *mdev = dev->mdev;
	unsigned long flags;
	int err = 0;
	int nreq;
	int ind;
	int i;

	if (unlikely(ibqp->qp_type == IB_QPT_GSI))
		return mlx5_ib_gsi_post_recv(ibqp, wr, bad_wr);

	spin_lock_irqsave(&qp->rq.lock, flags);

	if (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		err = -EIO;
		*bad_wr = wr;
		nreq = 0;
		goto out;
	}

	ind = qp->rq.head & (qp->rq.wqe_cnt - 1);

	for (nreq = 0; wr; nreq++, wr = wr->next) {
		if (mlx5_wq_overflow(&qp->rq, nreq, qp->ibqp.recv_cq)) {
			err = -ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		if (unlikely(wr->num_sge > qp->rq.max_gs)) {
			err = -EINVAL;
			*bad_wr = wr;
			goto out;
		}

		scat = get_recv_wqe(qp, ind);
		if (qp->wq_sig)
			scat++;

		for (i = 0; i < wr->num_sge; i++)
			set_data_ptr_seg(scat + i, wr->sg_list + i);

		if (i < qp->rq.max_gs) {
			scat[i].byte_count = 0;
			scat[i].lkey       = cpu_to_be32(MLX5_INVALID_LKEY);
			scat[i].addr       = 0;
		}

		if (qp->wq_sig) {
			sig = (struct mlx5_rwqe_sig *)scat;
			set_sig_seg(sig, (qp->rq.max_gs + 1) << 2);
		}

		qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (qp->rq.wqe_cnt - 1);
	}

out:
	if (likely(nreq)) {
		qp->rq.head += nreq;

		/* Make sure that descriptors are written before
		 * doorbell record.
		 */
		wmb();

		*qp->db.db = cpu_to_be32(qp->rq.head & 0xffff);
	}

	spin_unlock_irqrestore(&qp->rq.lock, flags);

	return err;
}