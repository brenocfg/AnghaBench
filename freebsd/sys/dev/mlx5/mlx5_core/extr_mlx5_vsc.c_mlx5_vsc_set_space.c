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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_dev {int vsc_addr; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ MLX5_VSC_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_VSC_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_VSC_SPACE_OFFSET ; 
 scalar_t__ MLX5_VSC_SPACE_SUPPORTED ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  status ; 

int mlx5_vsc_set_space(struct mlx5_core_dev *mdev, u16 space)
{
	device_t dev = mdev->pdev->dev.bsddev;
	int vsc_addr = mdev->vsc_addr;
	u32 vsc_space = 0;

	if (!vsc_addr) {
		mlx5_core_warn(mdev, "Unable to set vsc space, vsc_addr not initialized\n");
		return EINVAL;
	}

	MLX5_VSC_SET(vsc_space, &vsc_space, space, space);
	pci_write_config(dev, vsc_addr + MLX5_VSC_SPACE_OFFSET, vsc_space, 4);
	vsc_space = pci_read_config(dev, vsc_addr + MLX5_VSC_SPACE_OFFSET, 4);

	if (MLX5_VSC_GET(vsc_space, &vsc_space, status) != MLX5_VSC_SPACE_SUPPORTED) {
		mlx5_core_warn(mdev, "Space 0x%x is not supported.\n", space);
		return ENOTSUP;
	}

	return 0;
}