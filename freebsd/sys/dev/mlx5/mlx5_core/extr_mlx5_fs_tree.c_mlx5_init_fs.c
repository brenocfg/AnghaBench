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
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int init_egress_acl_root_ns (struct mlx5_core_dev*) ; 
 int init_fdb_root_ns (struct mlx5_core_dev*) ; 
 int init_ingress_acl_root_ns (struct mlx5_core_dev*) ; 
 int init_root_ns (struct mlx5_core_dev*) ; 
 int init_sniffer_rx_root_ns (struct mlx5_core_dev*) ; 
 int init_sniffer_tx_root_ns (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_fs (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  nic_flow_table ; 

int mlx5_init_fs(struct mlx5_core_dev *dev)
{
	int err;

	if (MLX5_CAP_GEN(dev, nic_flow_table)) {
		err = init_root_ns(dev);
		if (err)
			goto err;
	}

	err = init_fdb_root_ns(dev);
	if (err)
		goto err;

	err = init_egress_acl_root_ns(dev);
	if (err)
		goto err;

	err = init_ingress_acl_root_ns(dev);
	if (err)
		goto err;

	err = init_sniffer_tx_root_ns(dev);
	if (err)
		goto err;

	err = init_sniffer_rx_root_ns(dev);
	if (err)
		goto err;

	return 0;
err:
	mlx5_cleanup_fs(dev);
	return err;
}