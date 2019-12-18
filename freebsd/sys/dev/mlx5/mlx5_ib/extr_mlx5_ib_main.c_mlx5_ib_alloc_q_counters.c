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
struct mlx5_ib_dev {int num_ports; TYPE_1__* port; int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  q_cnt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_q_port_counter (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int) ; 
 int mlx5_vport_alloc_q_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_ib_alloc_q_counters(struct mlx5_ib_dev *dev)
{
	int i;
	int ret;

	for (i = 0; i < dev->num_ports; i++) {
		ret = mlx5_vport_alloc_q_counter(dev->mdev,
						 MLX5_INTERFACE_PROTOCOL_IB,
						 &dev->port[i].q_cnt_id);
		if (ret) {
			mlx5_ib_warn(dev,
				     "couldn't allocate queue counter for port %d, err %d\n",
				     i + 1, ret);
			goto dealloc_counters;
		}
	}

	return 0;

dealloc_counters:
	while (--i >= 0)
		mlx5_ib_dealloc_q_port_counter(dev, i);

	return ret;
}