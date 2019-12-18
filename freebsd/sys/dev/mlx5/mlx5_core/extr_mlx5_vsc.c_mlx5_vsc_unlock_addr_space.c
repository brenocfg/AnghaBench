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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MLX5_VSC_DOMAIN_SEMAPHORES ; 
 int mlx5_vsc_read (struct mlx5_core_dev*,scalar_t__,scalar_t__*) ; 
 int mlx5_vsc_set_space (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_vsc_write (struct mlx5_core_dev*,scalar_t__,scalar_t__*) ; 

int mlx5_vsc_unlock_addr_space(struct mlx5_core_dev *mdev, u32 addr)
{
	u32 data = 0;
	int ret;

	ret = mlx5_vsc_set_space(mdev, MLX5_VSC_DOMAIN_SEMAPHORES);
	if (ret)
		return ret;

	/* Try to modify lock */
	ret = mlx5_vsc_write(mdev, addr, &data);
	if (ret)
		return ret;

	/* Verify */
	ret = mlx5_vsc_read(mdev, addr, &data);
	if (ret)
		return ret;
	if (data != 0)
		return EBUSY;

	return 0;
}