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
struct mlx5dv_cq {int /*<<< orphan*/  uar; int /*<<< orphan*/  dbrec; int /*<<< orphan*/  buf; int /*<<< orphan*/  cqe_size; scalar_t__ cqe_cnt; int /*<<< orphan*/  cqn; scalar_t__ comp_mask; } ;
struct TYPE_3__ {scalar_t__ cqe; } ;
struct mlx5_cq {int /*<<< orphan*/  flags; int /*<<< orphan*/  dbrec; TYPE_2__* active_buf; int /*<<< orphan*/  cqe_sz; TYPE_1__ ibv_cq; int /*<<< orphan*/  cqn; } ;
struct mlx5_context {int /*<<< orphan*/  uar; } ;
struct ibv_cq {int /*<<< orphan*/  context; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CQ_FLAGS_DV_OWNED ; 
 struct mlx5_cq* to_mcq (struct ibv_cq*) ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5dv_get_cq(struct ibv_cq *cq_in,
			 struct mlx5dv_cq *cq_out)
{
	struct mlx5_cq *mcq = to_mcq(cq_in);
	struct mlx5_context *mctx = to_mctx(cq_in->context);

	cq_out->comp_mask = 0;
	cq_out->cqn       = mcq->cqn;
	cq_out->cqe_cnt   = mcq->ibv_cq.cqe + 1;
	cq_out->cqe_size  = mcq->cqe_sz;
	cq_out->buf       = mcq->active_buf->buf;
	cq_out->dbrec     = mcq->dbrec;
	cq_out->uar	  = mctx->uar;

	mcq->flags	 |= MLX5_CQ_FLAGS_DV_OWNED;

	return 0;
}