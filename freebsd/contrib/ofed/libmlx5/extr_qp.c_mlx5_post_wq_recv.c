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
struct TYPE_4__ {int /*<<< orphan*/  cq; } ;
struct mlx5_rwq {int wq_sig; TYPE_3__ rq; void** recv_db; TYPE_1__ wq; } ;
struct ibv_wq {int dummy; } ;
struct ibv_recv_wr {int num_sge; int /*<<< orphan*/  wr_id; TYPE_2__* sg_list; struct ibv_recv_wr* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MLX5_INVALID_LKEY ; 
 struct mlx5_wqe_data_seg* get_wq_recv_wqe (struct mlx5_rwq*,int) ; 
 void* htobe32 (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct mlx5_rwqe_sig*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 
 int mlx5_wq_overflow (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_data_ptr_seg (struct mlx5_wqe_data_seg*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wq_sig_seg (struct mlx5_rwq*,struct mlx5_rwqe_sig*,int,int) ; 
 int /*<<< orphan*/  to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx5_rwq* to_mrwq (struct ibv_wq*) ; 
 int /*<<< orphan*/  udma_to_device_barrier () ; 
 scalar_t__ unlikely (int) ; 

int mlx5_post_wq_recv(struct ibv_wq *ibwq, struct ibv_recv_wr *wr,
		      struct ibv_recv_wr **bad_wr)
{
	struct mlx5_rwq *rwq = to_mrwq(ibwq);
	struct mlx5_wqe_data_seg *scat;
	int err = 0;
	int nreq;
	int ind;
	int i, j;
	struct mlx5_rwqe_sig *sig;

	mlx5_spin_lock(&rwq->rq.lock);

	ind = rwq->rq.head & (rwq->rq.wqe_cnt - 1);

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		if (unlikely(mlx5_wq_overflow(&rwq->rq, nreq,
					      to_mcq(rwq->wq.cq)))) {
			err = ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		if (unlikely(wr->num_sge > rwq->rq.max_gs)) {
			err = EINVAL;
			*bad_wr = wr;
			goto out;
		}

		scat = get_wq_recv_wqe(rwq, ind);
		sig = (struct mlx5_rwqe_sig *)scat;
		if (unlikely(rwq->wq_sig)) {
			memset(sig, 0, 1 << rwq->rq.wqe_shift);
			++scat;
		}

		for (i = 0, j = 0; i < wr->num_sge; ++i) {
			if (unlikely(!wr->sg_list[i].length))
				continue;
			set_data_ptr_seg(scat + j++, wr->sg_list + i, 0);
		}

		if (j < rwq->rq.max_gs) {
			scat[j].byte_count = 0;
			scat[j].lkey       = htobe32(MLX5_INVALID_LKEY);
			scat[j].addr       = 0;
		}

		if (unlikely(rwq->wq_sig))
			set_wq_sig_seg(rwq, sig, (wr->num_sge + 1) << 4,
				       rwq->rq.head & 0xffff);

		rwq->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (rwq->rq.wqe_cnt - 1);
	}

out:
	if (likely(nreq)) {
		rwq->rq.head += nreq;
		/*
		 * Make sure that descriptors are written before
		 * doorbell record.
		 */
		udma_to_device_barrier();
		*(rwq->recv_db) = htobe32(rwq->rq.head & 0xffff);
	}

	mlx5_spin_unlock(&rwq->rq.lock);

	return err;
}