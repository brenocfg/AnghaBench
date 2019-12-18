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
struct mlx4_dev_persistent {int state; int /*<<< orphan*/  device_state_mutex; struct mlx4_dev* dev; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MLX4_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MLX4_DEV_EVENT_CATASTROPHIC_ERROR ; 
 int /*<<< orphan*/  mlx4_cmd_wake_completions (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_dispatch_event (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_internal_err_reset ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int mlx4_reset_master (struct mlx4_dev*) ; 
 int mlx4_reset_slave (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx4_enter_error_state(struct mlx4_dev_persistent *persist)
{
	int err;
	struct mlx4_dev *dev;

	if (!mlx4_internal_err_reset)
		return;

	mutex_lock(&persist->device_state_mutex);
	if (persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
		goto out;

	dev = persist->dev;
	mlx4_err(dev, "device is going to be reset\n");
	if (mlx4_is_slave(dev))
		err = mlx4_reset_slave(dev);
	else
		err = mlx4_reset_master(dev);
	BUG_ON(err != 0);

	dev->persist->state |= MLX4_DEVICE_STATE_INTERNAL_ERROR;
	mlx4_err(dev, "device was reset successfully\n");
	mutex_unlock(&persist->device_state_mutex);

	/* At that step HW was already reset, now notify clients */
	mlx4_dispatch_event(dev, MLX4_DEV_EVENT_CATASTROPHIC_ERROR, 0);
	mlx4_cmd_wake_completions(dev);
	return;

out:
	mutex_unlock(&persist->device_state_mutex);
}