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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_port_type_cap_to_rdma_ll (int) ; 
 int /*<<< orphan*/  port_type ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static enum rdma_link_layer
mlx5_ib_port_link_layer(struct ib_device *device, u8 port_num)
{
	struct mlx5_ib_dev *dev = to_mdev(device);
	int port_type_cap = MLX5_CAP_GEN(dev->mdev, port_type);

	return mlx5_port_type_cap_to_rdma_ll(port_type_cap);
}