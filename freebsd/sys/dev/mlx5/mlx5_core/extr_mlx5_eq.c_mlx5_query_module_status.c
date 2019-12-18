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
struct mlx5_core_dev {unsigned int* module_status; } ;

/* Variables and functions */
 int MLX5_MAX_PORTS ; 

unsigned int mlx5_query_module_status(struct mlx5_core_dev *dev, int module_num)
{
	if (module_num < 0 || module_num >= MLX5_MAX_PORTS)
		return 0;		/* undefined */
	return dev->module_status[module_num];
}