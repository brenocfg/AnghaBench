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
struct mlx5_context {TYPE_1__* uidx_table; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {scalar_t__ refcnt; int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 scalar_t__ MLX5_UIDX_TABLE_MASK ; 
 size_t MLX5_UIDX_TABLE_SHIFT ; 
 size_t MLX5_UIDX_TABLE_SIZE ; 

__attribute__((used)) static int32_t get_free_uidx(struct mlx5_context *ctx)
{
	int32_t tind;
	int32_t i;

	for (tind = 0; tind < MLX5_UIDX_TABLE_SIZE; tind++) {
		if (ctx->uidx_table[tind].refcnt < MLX5_UIDX_TABLE_MASK)
			break;
	}

	if (tind == MLX5_UIDX_TABLE_SIZE)
		return -1;

	if (!ctx->uidx_table[tind].refcnt)
		return tind << MLX5_UIDX_TABLE_SHIFT;

	for (i = 0; i < MLX5_UIDX_TABLE_MASK + 1; i++) {
		if (!ctx->uidx_table[tind].table[i])
			break;
	}

	return (tind << MLX5_UIDX_TABLE_SHIFT) | i;
}