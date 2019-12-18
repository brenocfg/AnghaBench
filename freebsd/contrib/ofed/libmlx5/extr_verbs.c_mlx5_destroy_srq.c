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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  rsn; } ;
struct mlx5_srq {struct mlx5_srq* wrid; int /*<<< orphan*/  buf; int /*<<< orphan*/  db; int /*<<< orphan*/  srqn; TYPE_1__ rsc; } ;
struct mlx5_context {scalar_t__ cqe_version; } ;
struct ibv_srq {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 scalar_t__ MLX5_RSC_TYPE_XSRQ ; 
 int /*<<< orphan*/  free (struct mlx5_srq*) ; 
 int ibv_cmd_destroy_srq (struct ibv_srq*) ; 
 int /*<<< orphan*/  mlx5_clear_srq (struct mlx5_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_clear_uidx (struct mlx5_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_free_db (struct mlx5_context*,int /*<<< orphan*/ ) ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 
 struct mlx5_srq* to_msrq (struct ibv_srq*) ; 

int mlx5_destroy_srq(struct ibv_srq *srq)
{
	int ret;
	struct mlx5_srq *msrq = to_msrq(srq);
	struct mlx5_context *ctx = to_mctx(srq->context);

	ret = ibv_cmd_destroy_srq(srq);
	if (ret)
		return ret;

	if (ctx->cqe_version && msrq->rsc.type == MLX5_RSC_TYPE_XSRQ)
		mlx5_clear_uidx(ctx, msrq->rsc.rsn);
	else
		mlx5_clear_srq(ctx, msrq->srqn);

	mlx5_free_db(ctx, msrq->db);
	mlx5_free_buf(&msrq->buf);
	free(msrq->wrid);
	free(msrq);

	return 0;
}