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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  bitmap; } ;
struct mlx5_core_dev {TYPE_1__ mpfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_MPFS_TABLE_MAX ; 
 scalar_t__ bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_destroy (int /*<<< orphan*/ *) ; 

void
mlx5_mpfs_destroy(struct mlx5_core_dev *dev)
{
	u32 num;

	num = bitmap_weight(dev->mpfs.bitmap, MLX5_MPFS_TABLE_MAX);
	if (num != 0)
		mlx5_core_err(dev, "Leaking %u MPFS MAC table entries\n", num);

	spin_lock_destroy(&dev->mpfs.spinlock);
}