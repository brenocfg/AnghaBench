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
struct mlx4_wqe_data_seg {scalar_t__ addr; void* lkey; scalar_t__ byte_count; } ;
struct TYPE_2__ {int head; int wqe_cnt; int max_gs; int /*<<< orphan*/  lock; int /*<<< orphan*/ * wrid; } ;
struct mlx4_qp {TYPE_1__ rq; void** db; } ;
struct ibv_recv_wr {int num_sge; int /*<<< orphan*/  wr_id; scalar_t__ sg_list; struct ibv_recv_wr* next; } ;
struct ibv_qp {int /*<<< orphan*/  recv_cq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX4_INVALID_LKEY ; 
 int /*<<< orphan*/  __set_data_seg (struct mlx4_wqe_data_seg*,scalar_t__) ; 
 struct mlx4_wqe_data_seg* get_recv_wqe (struct mlx4_qp*,int) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx4_qp* to_mqp (struct ibv_qp*) ; 
 int /*<<< orphan*/  udma_to_device_barrier () ; 
 scalar_t__ wq_overflow (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int mlx4_post_recv(struct ibv_qp *ibqp, struct ibv_recv_wr *wr,
		   struct ibv_recv_wr **bad_wr)
{
	struct mlx4_qp *qp = to_mqp(ibqp);
	struct mlx4_wqe_data_seg *scat;
	int ret = 0;
	int nreq;
	int ind;
	int i;

	pthread_spin_lock(&qp->rq.lock);

	/* XXX check that state is OK to post receive */

	ind = qp->rq.head & (qp->rq.wqe_cnt - 1);

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		if (wq_overflow(&qp->rq, nreq, to_mcq(ibqp->recv_cq))) {
			ret = ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		if (wr->num_sge > qp->rq.max_gs) {
			ret = ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		scat = get_recv_wqe(qp, ind);

		for (i = 0; i < wr->num_sge; ++i)
			__set_data_seg(scat + i, wr->sg_list + i);

		if (i < qp->rq.max_gs) {
			scat[i].byte_count = 0;
			scat[i].lkey       = htobe32(MLX4_INVALID_LKEY);
			scat[i].addr       = 0;
		}

		qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (qp->rq.wqe_cnt - 1);
	}

out:
	if (nreq) {
		qp->rq.head += nreq;

		/*
		 * Make sure that descriptors are written before
		 * doorbell record.
		 */
		udma_to_device_barrier();

		*qp->db = htobe32(qp->rq.head & 0xffff);
	}

	pthread_spin_unlock(&qp->rq.lock);

	return ret;
}