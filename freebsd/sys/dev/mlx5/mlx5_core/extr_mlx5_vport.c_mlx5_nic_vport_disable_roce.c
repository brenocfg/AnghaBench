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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int mlx5_nic_vport_enable_disable_roce (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

int mlx5_nic_vport_disable_roce(struct mlx5_core_dev *mdev)
{
	return mlx5_nic_vport_enable_disable_roce(mdev, 0);
}