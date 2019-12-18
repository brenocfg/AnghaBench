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
typedef  int u64 ;
struct mlx4_mac_table {int /*<<< orphan*/ * entries; int /*<<< orphan*/ * refs; } ;
struct mlx4_port_info {struct mlx4_mac_table mac_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_port_info* port; } ;

/* Variables and functions */
 int ENOENT ; 
 int MLX4_MAC_MASK ; 
 int MLX4_MAX_MAC_NUM ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_find_cached_mac(struct mlx4_dev *dev, u8 port, u64 mac, int *idx)
{
	struct mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	struct mlx4_mac_table *table = &info->mac_table;
	int i;

	for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
		if (!table->refs[i])
			continue;

		if (mac == (MLX4_MAC_MASK & be64_to_cpu(table->entries[i]))) {
			*idx = i;
			return 0;
		}
	}

	return -ENOENT;
}