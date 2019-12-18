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
typedef  int u64 ;
struct mlx4_mac_table {int /*<<< orphan*/ * entries; scalar_t__* refs; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_MAC_MASK ; 
 int MLX4_MAX_MAC_NUM ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_index(struct mlx4_dev *dev,
		      struct mlx4_mac_table *table, u64 mac)
{
	int i;

	for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
		if (table->refs[i] &&
		    (MLX4_MAC_MASK & mac) ==
		    (MLX4_MAC_MASK & be64_to_cpu(table->entries[i])))
			return i;
	}
	/* Mac not found */
	return -EINVAL;
}