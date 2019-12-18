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
struct mlx4_mac_table {int* is_dup; int max; scalar_t__ total; scalar_t__* refs; scalar_t__* entries; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int log_num_macs; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_MAX_MAC_NUM ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void mlx4_init_mac_table(struct mlx4_dev *dev, struct mlx4_mac_table *table)
{
	int i;

	mutex_init(&table->mutex);
	for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
		table->entries[i] = 0;
		table->refs[i]	 = 0;
		table->is_dup[i] = false;
	}
	table->max   = 1 << dev->caps.log_num_macs;
	table->total = 0;
}