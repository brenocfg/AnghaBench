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
struct mlx5_resource {int dummy; } ;
struct mlx5_context {int /*<<< orphan*/  uidx_table_mutex; TYPE_1__* uidx_table; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {void** table; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int MLX5_UIDX_TABLE_MASK ; 
 size_t MLX5_UIDX_TABLE_SHIFT ; 
 void** calloc (int,int) ; 
 size_t get_free_uidx (struct mlx5_context*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int32_t mlx5_store_uidx(struct mlx5_context *ctx, void *rsc)
{
	int32_t tind;
	int32_t ret = -1;
	int32_t uidx;

	pthread_mutex_lock(&ctx->uidx_table_mutex);
	uidx = get_free_uidx(ctx);
	if (uidx < 0)
		goto out;

	tind = uidx >> MLX5_UIDX_TABLE_SHIFT;

	if (!ctx->uidx_table[tind].refcnt) {
		ctx->uidx_table[tind].table = calloc(MLX5_UIDX_TABLE_MASK + 1,
						     sizeof(struct mlx5_resource *));
		if (!ctx->uidx_table[tind].table)
			goto out;
	}

	++ctx->uidx_table[tind].refcnt;
	ctx->uidx_table[tind].table[uidx & MLX5_UIDX_TABLE_MASK] = rsc;
	ret = uidx;

out:
	pthread_mutex_unlock(&ctx->uidx_table_mutex);
	return ret;
}