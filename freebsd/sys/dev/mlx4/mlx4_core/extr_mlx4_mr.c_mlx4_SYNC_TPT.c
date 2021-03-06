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
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_SYNC_TPT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_SYNC_TPT(struct mlx4_dev *dev)
{
	return mlx4_cmd(dev, 0, 0, 0, MLX4_CMD_SYNC_TPT,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
}