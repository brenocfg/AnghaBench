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
struct mlx4_ib_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int mlx4_get_base_gid_ix (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ rdma_port_get_link_layer (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_slave_base_gid_ix(struct mlx4_ib_dev *dev, int slave, int port)
{
	if (rdma_port_get_link_layer(&dev->ib_dev, port) == IB_LINK_LAYER_INFINIBAND)
		return slave;
	return mlx4_get_base_gid_ix(dev->dev, slave, port);
}