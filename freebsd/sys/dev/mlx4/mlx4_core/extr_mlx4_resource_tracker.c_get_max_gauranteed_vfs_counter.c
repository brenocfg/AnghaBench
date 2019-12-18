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
struct TYPE_2__ {int max_counters; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_MAX_PORTS ; 
 int MLX4_PF_COUNTERS_PER_PORT ; 

__attribute__((used)) static int get_max_gauranteed_vfs_counter(struct mlx4_dev *dev)
{
	/* reduce the sink counter */
	return (dev->caps.max_counters - 1 -
		(MLX4_PF_COUNTERS_PER_PORT * MLX4_MAX_PORTS))
		/ MLX4_MAX_PORTS;
}