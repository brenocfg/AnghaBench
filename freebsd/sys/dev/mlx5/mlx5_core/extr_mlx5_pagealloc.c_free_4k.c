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
typedef  scalar_t__ u64 ;
struct mlx5_fw_page {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_DMA_LOCK (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  MLX5_DMA_UNLOCK (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,long long) ; 
 int /*<<< orphan*/  mlx5_fwp_free (struct mlx5_fw_page*) ; 
 struct mlx5_fw_page* mlx5_remove_fw_page_locked (struct mlx5_core_dev*,scalar_t__) ; 

__attribute__((used)) static void
free_4k(struct mlx5_core_dev *dev, u64 addr)
{
	struct mlx5_fw_page *fwp;

	MLX5_DMA_LOCK(dev);
	fwp = mlx5_remove_fw_page_locked(dev, addr);
	MLX5_DMA_UNLOCK(dev);

	if (fwp == NULL) {
		mlx5_core_warn(dev, "Cannot free 4K page at 0x%llx\n", (long long)addr);
		return;
	}
	mlx5_fwp_free(fwp);
}