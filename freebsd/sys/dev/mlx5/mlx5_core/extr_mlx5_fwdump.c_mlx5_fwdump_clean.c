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
struct mlx5_core_dev {int /*<<< orphan*/  dump_rege; int /*<<< orphan*/  dump_lock; scalar_t__ dump_copyout; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MLX5_DUMP ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fwdump_destroy_dd (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
mlx5_fwdump_clean(struct mlx5_core_dev *mdev)
{

	mtx_lock(&mdev->dump_lock);
	while (mdev->dump_copyout)
		msleep(&mdev->dump_copyout, &mdev->dump_lock, 0, "mlx5fwc", 0);
	mlx5_fwdump_destroy_dd(mdev);
	mtx_unlock(&mdev->dump_lock);
	free(mdev->dump_rege, M_MLX5_DUMP);
}