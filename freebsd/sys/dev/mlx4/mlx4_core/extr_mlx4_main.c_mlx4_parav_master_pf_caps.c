#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* pkey_phys_table_len; } ;
struct TYPE_4__ {int num_ports; scalar_t__* port_type; int* gid_table_len; scalar_t__* pkey_table_len; } ;
struct mlx4_dev {TYPE_1__ phys_caps; TYPE_2__ caps; } ;

/* Variables and functions */
 scalar_t__ MLX4_PORT_TYPE_ETH ; 
 int mlx4_get_slave_num_gids (struct mlx4_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mlx4_parav_master_pf_caps(struct mlx4_dev *dev)
{
	int i;

	for (i = 1; i <= dev->caps.num_ports; i++) {
		if (dev->caps.port_type[i] == MLX4_PORT_TYPE_ETH)
			dev->caps.gid_table_len[i] =
				mlx4_get_slave_num_gids(dev, 0, i);
		else
			dev->caps.gid_table_len[i] = 1;
		dev->caps.pkey_table_len[i] =
			dev->phys_caps.pkey_phys_table_len[i] - 1;
	}
}