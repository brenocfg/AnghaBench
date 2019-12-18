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
struct mlx5_srq {int dummy; } ;
struct mlx5_context {TYPE_1__* srq_table; } ;
struct TYPE_2__ {struct mlx5_srq** table; scalar_t__ refcnt; } ;

/* Variables and functions */
 size_t MLX5_SRQ_TABLE_MASK ; 
 size_t MLX5_SRQ_TABLE_SHIFT ; 

struct mlx5_srq *mlx5_find_srq(struct mlx5_context *ctx, uint32_t srqn)
{
	int tind = srqn >> MLX5_SRQ_TABLE_SHIFT;

	if (ctx->srq_table[tind].refcnt)
		return ctx->srq_table[tind].table[srqn & MLX5_SRQ_TABLE_MASK];
	else
		return NULL;
}