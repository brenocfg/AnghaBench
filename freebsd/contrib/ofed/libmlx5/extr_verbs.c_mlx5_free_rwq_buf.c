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
struct TYPE_2__ {int /*<<< orphan*/  wrid; } ;
struct mlx5_rwq {TYPE_1__ rq; int /*<<< orphan*/  buf; } ;
struct mlx5_context {int dummy; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_actual_buf (struct mlx5_context*,int /*<<< orphan*/ *) ; 
 struct mlx5_context* to_mctx (struct ibv_context*) ; 

__attribute__((used)) static void mlx5_free_rwq_buf(struct mlx5_rwq *rwq, struct ibv_context *context)
{
	struct mlx5_context *ctx = to_mctx(context);

	mlx5_free_actual_buf(ctx, &rwq->buf);
	free(rwq->rq.wrid);
}