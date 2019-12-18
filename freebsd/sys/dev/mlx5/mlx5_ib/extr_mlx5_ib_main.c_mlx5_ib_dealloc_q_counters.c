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
struct mlx5_ib_dev {unsigned int num_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_ib_dealloc_q_port_counter (struct mlx5_ib_dev*,unsigned int) ; 

__attribute__((used)) static void mlx5_ib_dealloc_q_counters(struct mlx5_ib_dev *dev)
{
	unsigned int i;

	for (i = 0; i < dev->num_ports; i++)
		mlx5_ib_dealloc_q_port_counter(dev, i);
}