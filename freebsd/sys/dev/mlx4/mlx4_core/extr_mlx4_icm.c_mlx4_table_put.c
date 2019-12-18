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
typedef  int u64 ;
typedef  int u32 ;
struct mlx4_icm_table {int num_obj; int obj_size; int /*<<< orphan*/  mutex; TYPE_1__** icm; int /*<<< orphan*/  coherent; scalar_t__ virt; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ refcount; } ;

/* Variables and functions */
 int MLX4_ICM_PAGE_SIZE ; 
 int MLX4_TABLE_CHUNK_SIZE ; 
 int /*<<< orphan*/  mlx4_UNMAP_ICM (struct mlx4_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mlx4_free_icm (struct mlx4_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx4_table_put(struct mlx4_dev *dev, struct mlx4_icm_table *table, u32 obj)
{
	u32 i;
	u64 offset;

	i = (obj & (table->num_obj - 1)) / (MLX4_TABLE_CHUNK_SIZE / table->obj_size);

	mutex_lock(&table->mutex);

	if (--table->icm[i]->refcount == 0) {
		offset = (u64) i * MLX4_TABLE_CHUNK_SIZE;
		mlx4_UNMAP_ICM(dev, table->virt + offset,
			       MLX4_TABLE_CHUNK_SIZE / MLX4_ICM_PAGE_SIZE);
		mlx4_free_icm(dev, table->icm[i], table->coherent);
		table->icm[i] = NULL;
	}

	mutex_unlock(&table->mutex);
}