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
struct mlx5_core_dev {TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int BUS_RESET_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVF_RESET_DETACH ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MLX5_FRL_LEVEL3 ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int mlx5_set_mfrl_reg (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlx5_fw_reset(struct mlx5_core_dev *mdev)
{
	device_t dev, bus;
	int error;

	error = -mlx5_set_mfrl_reg(mdev, MLX5_FRL_LEVEL3);
	if (error == 0) {
		dev = mdev->pdev->dev.bsddev;
		mtx_lock(&Giant);
		bus = device_get_parent(dev);
		error = BUS_RESET_CHILD(device_get_parent(bus), bus,
		    DEVF_RESET_DETACH);
		mtx_unlock(&Giant);
	}
	return (error);
}