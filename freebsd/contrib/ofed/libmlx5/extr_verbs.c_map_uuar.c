#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_qp {int /*<<< orphan*/ * bf; } ;
struct mlx5_context {int /*<<< orphan*/ * bfs; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 struct mlx5_context* to_mctx (struct ibv_context*) ; 

__attribute__((used)) static void map_uuar(struct ibv_context *context, struct mlx5_qp *qp,
		     int uuar_index)
{
	struct mlx5_context *ctx = to_mctx(context);

	qp->bf = &ctx->bfs[uuar_index];
}