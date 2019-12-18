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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CMD_MODE_POLLING ; 
 int /*<<< orphan*/  mlx5_cmd_change_mod (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

void mlx5_cmd_use_polling(struct mlx5_core_dev *dev)
{
        mlx5_cmd_change_mod(dev, MLX5_CMD_MODE_POLLING);
}