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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ fatal_error; } ;
struct TYPE_4__ {TYPE_1__ health; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;

/* Variables and functions */
 scalar_t__ MLX5_NIC_IFC_SW_RESET ; 
 scalar_t__ MLX5_SENSOR_PCI_COMM_ERR ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_disable_device (struct mlx5_core_dev*) ; 
 scalar_t__ mlx5_get_nic_state (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5_handle_bad_state(struct mlx5_core_dev *dev)
{
	u8 nic_mode = mlx5_get_nic_state(dev);

	if (nic_mode == MLX5_NIC_IFC_SW_RESET) {
		/* The IFC mode field is 3 bits, so it will read 0x7 in two cases:
		 * 1. PCI has been disabled (ie. PCI-AER, PF driver unloaded
		 *    and this is a VF), this is not recoverable by SW reset.
		 *    Logging of this is handled elsewhere.
		 * 2. FW reset has been issued by another function, driver can
		 *    be reloaded to recover after the mode switches to
		 *    MLX5_NIC_IFC_DISABLED.
		 */
		if (dev->priv.health.fatal_error != MLX5_SENSOR_PCI_COMM_ERR)
			mlx5_core_warn(dev,
			    "NIC SW reset is already progress\n");
		else
			mlx5_core_warn(dev,
			    "Communication with FW over the PCI link is down\n");
	} else {
		mlx5_core_warn(dev, "NIC mode %d\n", nic_mode);
	}

	mlx5_disable_device(dev);
}