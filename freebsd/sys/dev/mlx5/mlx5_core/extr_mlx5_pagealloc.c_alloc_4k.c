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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_fw_page {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  func_id; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_DMA_LOCK (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  MLX5_DMA_UNLOCK (struct mlx5_core_dev*) ; 
 struct mlx5_fw_page* mlx5_fwp_alloc (struct mlx5_core_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fwp_free (struct mlx5_fw_page*) ; 
 int /*<<< orphan*/  mlx5_fwp_invalidate (struct mlx5_fw_page*) ; 
 int mlx5_insert_fw_page_locked (struct mlx5_core_dev*,struct mlx5_fw_page*) ; 

__attribute__((used)) static int
alloc_4k(struct mlx5_core_dev *dev, u64 *addr, u16 func_id)
{
	struct mlx5_fw_page *fwp;
	int err;

	fwp = mlx5_fwp_alloc(dev, GFP_KERNEL, 1);
	if (fwp == NULL)
		return (-ENOMEM);

	fwp->func_id = func_id;

	MLX5_DMA_LOCK(dev);
	err = mlx5_insert_fw_page_locked(dev, fwp);
	MLX5_DMA_UNLOCK(dev);

	if (err != 0) {
		mlx5_fwp_free(fwp);
	} else {
		/* make sure cached data is cleaned */
		mlx5_fwp_invalidate(fwp);

		/* store DMA address */
		*addr = fwp->dma_addr;
	}
	return (err);
}