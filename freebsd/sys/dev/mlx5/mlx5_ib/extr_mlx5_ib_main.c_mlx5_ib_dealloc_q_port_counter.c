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
typedef  size_t u8 ;
struct mlx5_ib_dev {TYPE_1__* port; int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {scalar_t__ q_cnt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int /*<<< orphan*/  mlx5_vport_dealloc_q_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mlx5_ib_dealloc_q_port_counter(struct mlx5_ib_dev *dev, u8 port_num)
{
	mlx5_vport_dealloc_q_counter(dev->mdev,
				     MLX5_INTERFACE_PROTOCOL_IB,
				     dev->port[port_num].q_cnt_id);
	dev->port[port_num].q_cnt_id = 0;
}