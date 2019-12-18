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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
#define  MLX5_CMD_HCA_CAP_PORT_TYPE_ETHERNET 129 
#define  MLX5_CMD_HCA_CAP_PORT_TYPE_IB 128 
 int mlx5_query_hca_vport_port_guid (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_query_nic_vport_port_guid (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_type ; 

int mlx5_query_vport_port_guid(struct mlx5_core_dev *dev, u64 *port_guid)
{
	switch (MLX5_CAP_GEN(dev, port_type)) {
	case MLX5_CMD_HCA_CAP_PORT_TYPE_IB:
		return mlx5_query_hca_vport_port_guid(dev, port_guid);

	case MLX5_CMD_HCA_CAP_PORT_TYPE_ETHERNET:
		return mlx5_query_nic_vport_port_guid(dev, port_guid);

	default:
		return -EINVAL;
	}
}