#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_dev {int /*<<< orphan*/  ib_dev; } ;
struct TYPE_2__ {int sgid_index; } ;
struct ib_ah_attr {TYPE_1__ grh; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 scalar_t__ get_slave_base_gid_ix (struct mlx4_ib_dev*,int,int) ; 
 scalar_t__ rdma_port_get_link_layer (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fill_in_real_sgid_index(struct mlx4_ib_dev *dev, int slave, int port,
				    struct ib_ah_attr *ah_attr)
{
	if (rdma_port_get_link_layer(&dev->ib_dev, port) == IB_LINK_LAYER_INFINIBAND)
		ah_attr->grh.sgid_index = slave;
	else
		ah_attr->grh.sgid_index += get_slave_base_gid_ix(dev, slave, port);
}