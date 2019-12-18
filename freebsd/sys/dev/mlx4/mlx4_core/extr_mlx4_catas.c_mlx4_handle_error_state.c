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
struct mlx4_dev_persistent {int interface_state; int /*<<< orphan*/  interface_state_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int MLX4_INTERFACE_STATE_DELETION ; 
 int MLX4_INTERFACE_STATE_UP ; 
 int /*<<< orphan*/  mlx4_enter_error_state (struct mlx4_dev_persistent*) ; 
 int /*<<< orphan*/  mlx4_info (int /*<<< orphan*/ ,char*,int) ; 
 int mlx4_restart_one (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_handle_error_state(struct mlx4_dev_persistent *persist)
{
	int err = 0;

	mlx4_enter_error_state(persist);
	mutex_lock(&persist->interface_state_mutex);
	if (persist->interface_state & MLX4_INTERFACE_STATE_UP &&
	    !(persist->interface_state & MLX4_INTERFACE_STATE_DELETION)) {
		err = mlx4_restart_one(persist->pdev);
		mlx4_info(persist->dev, "mlx4_restart_one was ended, ret=%d\n",
			  err);
	}
	mutex_unlock(&persist->interface_state_mutex);
}