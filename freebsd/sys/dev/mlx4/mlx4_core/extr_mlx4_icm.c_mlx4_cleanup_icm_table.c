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
struct mlx4_icm_table {int num_icm; scalar_t__* icm; int /*<<< orphan*/  coherent; scalar_t__ virt; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int MLX4_ICM_PAGE_SIZE ; 
 int MLX4_TABLE_CHUNK_SIZE ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_UNMAP_ICM (struct mlx4_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mlx4_free_icm (struct mlx4_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

void mlx4_cleanup_icm_table(struct mlx4_dev *dev, struct mlx4_icm_table *table)
{
	int i;

	for (i = 0; i < table->num_icm; ++i)
		if (table->icm[i]) {
			mlx4_UNMAP_ICM(dev, table->virt + i * MLX4_TABLE_CHUNK_SIZE,
				       MLX4_TABLE_CHUNK_SIZE / MLX4_ICM_PAGE_SIZE);
			mlx4_free_icm(dev, table->icm[i], table->coherent);
		}

	kfree(table->icm);
}