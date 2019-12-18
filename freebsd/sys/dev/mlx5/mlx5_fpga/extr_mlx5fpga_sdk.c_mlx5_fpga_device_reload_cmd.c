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
struct mlx5_fpga_device {int /*<<< orphan*/  state_lock; void* fdev_state; int /*<<< orphan*/  load_event; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 void* MLX5_FDEV_STATE_FAILURE ; 
 void* MLX5_FDEV_STATE_IN_PROGRESS ; 
 void* MLX5_FDEV_STATE_SUCCESS ; 
 int /*<<< orphan*/  MLX5_FPGA_CTRL_OPERATION_RELOAD ; 
 int /*<<< orphan*/  MLX5_FPGA_LOAD_TIMEOUT ; 
 unsigned long jiffies ; 
 int mlx5_fpga_ctrl_op (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_fpga_device_start (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int) ; 
 int /*<<< orphan*/  mlx5_fpga_info (struct mlx5_fpga_device*,char*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mlx5_fpga_device_reload_cmd(struct mlx5_fpga_device *fdev)
{
	struct mlx5_core_dev *mdev = fdev->mdev;
	unsigned long timeout;
	unsigned long flags;
	int err = 0;

	mlx5_fpga_info(fdev, "mlx5/fpga - reload started\n");
	fdev->fdev_state = MLX5_FDEV_STATE_IN_PROGRESS;
	reinit_completion(&fdev->load_event);
	err = mlx5_fpga_ctrl_op(mdev, MLX5_FPGA_CTRL_OPERATION_RELOAD);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to request reload: %d\n",
			      err);
		goto out;
	}
	timeout = jiffies + msecs_to_jiffies(MLX5_FPGA_LOAD_TIMEOUT);
	err = wait_for_completion_timeout(&fdev->load_event,
					  timeout - jiffies);
	if (err < 0) {
		mlx5_fpga_err(fdev, "Failed waiting for reload: %d\n", err);
		fdev->fdev_state = MLX5_FDEV_STATE_FAILURE;
		goto out;
	}
	/* Check device loaded successful */
	err = mlx5_fpga_device_start(mdev);
	if (err) {
		mlx5_fpga_err(fdev, "Failed load check for reload: %d\n", err);
		fdev->fdev_state = MLX5_FDEV_STATE_FAILURE;
		goto out;
	}
	spin_lock_irqsave(&fdev->state_lock, flags);
	fdev->fdev_state = MLX5_FDEV_STATE_SUCCESS;
	spin_unlock_irqrestore(&fdev->state_lock, flags);
	mlx5_fpga_info(fdev, "mlx5/fpga - reload ended\n");
out:
	return err;
}