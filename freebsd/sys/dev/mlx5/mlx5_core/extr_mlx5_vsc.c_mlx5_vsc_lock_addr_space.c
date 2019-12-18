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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {int vsc_addr; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MLX5_VSC_COUNTER_OFFSET ; 
 int /*<<< orphan*/  MLX5_VSC_DOMAIN_SEMAPHORES ; 
 int mlx5_vsc_read (struct mlx5_core_dev*,scalar_t__,scalar_t__*) ; 
 int mlx5_vsc_set_space (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_vsc_write (struct mlx5_core_dev*,scalar_t__,scalar_t__*) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

int mlx5_vsc_lock_addr_space(struct mlx5_core_dev *mdev, u32 addr)
{
	device_t dev = mdev->pdev->dev.bsddev;
	int vsc_addr = mdev->vsc_addr;
	u32 data;
	int ret;
	u32 id;

	ret = mlx5_vsc_set_space(mdev, MLX5_VSC_DOMAIN_SEMAPHORES);
	if (ret)
		return ret;

	/* Get a unique ID based on the counter */
	id = pci_read_config(dev, vsc_addr + MLX5_VSC_COUNTER_OFFSET, 4);

	/* Try to modify lock */
	ret = mlx5_vsc_write(mdev, addr, &id);
	if (ret)
		return ret;

	/* Verify */
	ret = mlx5_vsc_read(mdev, addr, &data);
	if (ret)
		return ret;
	if (data != id)
		return EBUSY;

	return 0;
}