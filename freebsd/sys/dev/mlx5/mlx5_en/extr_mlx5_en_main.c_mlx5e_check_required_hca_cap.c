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
 int ENODEV ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static int
mlx5e_check_required_hca_cap(struct mlx5_core_dev *mdev)
{
	/*
	 * TODO: uncoment once FW really sets all these bits if
	 * (!mdev->caps.eth.rss_ind_tbl_cap || !mdev->caps.eth.csum_cap ||
	 * !mdev->caps.eth.max_lso_cap || !mdev->caps.eth.vlan_cap ||
	 * !(mdev->caps.gen.flags & MLX5_DEV_CAP_FLAG_SCQE_BRK_MOD)) return
	 * -ENOTSUPP;
	 */

	/* TODO: add more must-to-have features */

	if (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		return (-ENODEV);

	return (0);
}