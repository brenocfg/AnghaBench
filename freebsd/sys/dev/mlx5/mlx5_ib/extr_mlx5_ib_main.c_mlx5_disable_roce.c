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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_nic_vport_disable_roce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_roce_lag_cleanup (struct mlx5_ib_dev*) ; 

__attribute__((used)) static void mlx5_disable_roce(struct mlx5_ib_dev *dev)
{
	mlx5_roce_lag_cleanup(dev);
	mlx5_nic_vport_disable_roce(dev->mdev);
}