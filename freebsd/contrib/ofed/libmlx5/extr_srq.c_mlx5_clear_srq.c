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
typedef  size_t uint32_t ;
struct mlx5_context {TYPE_1__* srq_table; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** table; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 size_t MLX5_QP_TABLE_SHIFT ; 
 size_t MLX5_SRQ_TABLE_MASK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 

void mlx5_clear_srq(struct mlx5_context *ctx, uint32_t srqn)
{
	int tind = srqn >> MLX5_QP_TABLE_SHIFT;

	if (!--ctx->srq_table[tind].refcnt)
		free(ctx->srq_table[tind].table);
	else
		ctx->srq_table[tind].table[srqn & MLX5_SRQ_TABLE_MASK] = NULL;
}