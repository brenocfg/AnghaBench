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
typedef  size_t uint16_t ;
struct mlx5_wq {int tail; int wqe_cnt; int /*<<< orphan*/ * wrid; } ;
struct mlx5_srq {int /*<<< orphan*/ * wrid; } ;
struct mlx5_resource {scalar_t__ type; } ;
struct mlx5_qp {int qp_cap_cache; struct mlx5_wq rq; } ;
struct mlx5_cqe64 {int op_own; int /*<<< orphan*/  byte_cnt; int /*<<< orphan*/  wqe_counter; } ;
struct TYPE_3__ {int /*<<< orphan*/  wr_id; } ;
struct mlx5_cq {TYPE_1__ ibv_cq; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {struct mlx5_wq rq; } ;

/* Variables and functions */
 int IBV_WC_SUCCESS ; 
 int /*<<< orphan*/  MLX5_CQ_FLAGS_RX_CSUM_VALID ; 
 int MLX5_INLINE_SCATTER_32 ; 
 int MLX5_INLINE_SCATTER_64 ; 
 scalar_t__ MLX5_RSC_TYPE_QP ; 
 int MLX5_RX_CSUM_VALID ; 
 size_t be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int mlx5_copy_to_recv_srq (struct mlx5_srq*,size_t,struct mlx5_cqe64*,int /*<<< orphan*/ ) ; 
 int mlx5_copy_to_recv_wqe (struct mlx5_qp*,size_t,struct mlx5_cqe64*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_srq_wqe (struct mlx5_srq*,size_t) ; 
 struct mlx5_qp* rsc_to_mqp (struct mlx5_resource*) ; 
 TYPE_2__* rsc_to_mrwq (struct mlx5_resource*) ; 

__attribute__((used)) static inline int handle_responder_lazy(struct mlx5_cq *cq, struct mlx5_cqe64 *cqe,
					struct mlx5_resource *cur_rsc, struct mlx5_srq *srq)
{
	uint16_t	wqe_ctr;
	struct mlx5_wq *wq;
	struct mlx5_qp *qp = rsc_to_mqp(cur_rsc);
	int err = IBV_WC_SUCCESS;

	if (srq) {
		wqe_ctr = be16toh(cqe->wqe_counter);
		cq->ibv_cq.wr_id = srq->wrid[wqe_ctr];
		mlx5_free_srq_wqe(srq, wqe_ctr);
		if (cqe->op_own & MLX5_INLINE_SCATTER_32)
			err = mlx5_copy_to_recv_srq(srq, wqe_ctr, cqe,
						    be32toh(cqe->byte_cnt));
		else if (cqe->op_own & MLX5_INLINE_SCATTER_64)
			err = mlx5_copy_to_recv_srq(srq, wqe_ctr, cqe - 1,
						    be32toh(cqe->byte_cnt));
	} else {
		if (likely(cur_rsc->type == MLX5_RSC_TYPE_QP)) {
			wq = &qp->rq;
			if (qp->qp_cap_cache & MLX5_RX_CSUM_VALID)
				cq->flags |= MLX5_CQ_FLAGS_RX_CSUM_VALID;
		} else {
			wq = &(rsc_to_mrwq(cur_rsc)->rq);
		}

		wqe_ctr = wq->tail & (wq->wqe_cnt - 1);
		cq->ibv_cq.wr_id = wq->wrid[wqe_ctr];
		++wq->tail;
		if (cqe->op_own & MLX5_INLINE_SCATTER_32)
			err = mlx5_copy_to_recv_wqe(qp, wqe_ctr, cqe,
						    be32toh(cqe->byte_cnt));
		else if (cqe->op_own & MLX5_INLINE_SCATTER_64)
			err = mlx5_copy_to_recv_wqe(qp, wqe_ctr, cqe - 1,
						    be32toh(cqe->byte_cnt));
	}

	return err;
}