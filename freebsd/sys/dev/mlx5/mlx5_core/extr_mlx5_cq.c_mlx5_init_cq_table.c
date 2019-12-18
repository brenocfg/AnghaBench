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
struct mlx5_cq_table {int /*<<< orphan*/  tree; TYPE_2__* linear_array; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct mlx5_cq_table cq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_CQ_LINEAR_ARRAY_SIZE ; 
 int /*<<< orphan*/  memset (struct mlx5_cq_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5_init_cq_table(struct mlx5_core_dev *dev)
{
	struct mlx5_cq_table *table = &dev->priv.cq_table;
	int err;
	int x;

	memset(table, 0, sizeof(*table));
	spin_lock_init(&table->lock);
	for (x = 0; x != MLX5_CQ_LINEAR_ARRAY_SIZE; x++)
		spin_lock_init(&table->linear_array[x].lock);
	INIT_RADIX_TREE(&table->tree, GFP_ATOMIC);
	err = 0;

	return err;
}