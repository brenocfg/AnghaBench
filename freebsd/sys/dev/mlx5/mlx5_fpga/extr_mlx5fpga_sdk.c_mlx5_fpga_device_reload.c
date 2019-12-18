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
struct mlx5_fpga_device {int fdev_state; int /*<<< orphan*/  load_event; int /*<<< orphan*/  state_lock; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int /*<<< orphan*/  intf_state_mutex; int /*<<< orphan*/  intf_state; } ;
typedef  enum mlx5_fpga_image { ____Placeholder_mlx5_fpga_image } mlx5_fpga_image ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
#define  MLX5_FDEV_STATE_DISCONNECTED 132 
#define  MLX5_FDEV_STATE_FAILURE 131 
#define  MLX5_FDEV_STATE_IN_PROGRESS 130 
#define  MLX5_FDEV_STATE_NONE 129 
#define  MLX5_FDEV_STATE_SUCCESS 128 
 int /*<<< orphan*/  MLX5_FPGA_CTRL_OPERATION_RESET ; 
 int MLX5_FPGA_IMAGE_FACTORY ; 
 int MLX5_FPGA_IMAGE_RELOAD ; 
 int MLX5_FPGA_IMAGE_RESET ; 
 int /*<<< orphan*/  MLX5_FPGA_LOAD_TIMEOUT ; 
 int /*<<< orphan*/  MLX5_INTERFACE_STATE_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_fpga_ctrl_op (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_fpga_device_reload_cmd (struct mlx5_fpga_device*) ; 
 int mlx5_fpga_device_start (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_device_stop (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int) ; 
 int /*<<< orphan*/  mlx5_fpga_info (struct mlx5_fpga_device*,char*) ; 
 int mlx5_fpga_load (struct mlx5_core_dev*,int) ; 
 int mlx5_register_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_unregister_device (struct mlx5_core_dev*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

int mlx5_fpga_device_reload(struct mlx5_fpga_device *fdev,
			    enum mlx5_fpga_image image)
{
	struct mlx5_core_dev *mdev = fdev->mdev;
	unsigned long timeout;
	unsigned long flags;
	int err = 0;

	spin_lock_irqsave(&fdev->state_lock, flags);
	switch (fdev->fdev_state) {
	case MLX5_FDEV_STATE_NONE:
		err = -ENODEV;
		break;
	case MLX5_FDEV_STATE_IN_PROGRESS:
		err = -EBUSY;
		break;
	case MLX5_FDEV_STATE_SUCCESS:
	case MLX5_FDEV_STATE_FAILURE:
	case MLX5_FDEV_STATE_DISCONNECTED:
		break;
	}
	spin_unlock_irqrestore(&fdev->state_lock, flags);
	if (err)
		return err;

	mutex_lock(&mdev->intf_state_mutex);

	if (image == MLX5_FPGA_IMAGE_RELOAD) {
		err = mlx5_fpga_device_reload_cmd(fdev);
		goto out;
	}

	clear_bit(MLX5_INTERFACE_STATE_UP, &mdev->intf_state);

	mlx5_unregister_device(mdev);
	/* XXXKIB	mlx5_accel_ipsec_cleanup(mdev); */
	mlx5_fpga_device_stop(mdev);

	fdev->fdev_state = MLX5_FDEV_STATE_IN_PROGRESS;
	reinit_completion(&fdev->load_event);

	if (image <= MLX5_FPGA_IMAGE_FACTORY) {
		mlx5_fpga_info(fdev, "Loading from flash\n");
		err = mlx5_fpga_load(mdev, image);
		if (err) {
			mlx5_fpga_err(fdev, "Failed to request load: %d\n",
				      err);
			goto out;
		}
	} else if (image == MLX5_FPGA_IMAGE_RESET) {
		mlx5_fpga_info(fdev, "Resetting\n");
		err = mlx5_fpga_ctrl_op(mdev, MLX5_FPGA_CTRL_OPERATION_RESET);
		if (err) {
			mlx5_fpga_err(fdev, "Failed to request reset: %d\n",
				      err);
			goto out;
		}
	} else {
		mlx5_fpga_err(fdev, "Unknown command: %d\n",
			      image);
		goto out;
	}

	timeout = jiffies + msecs_to_jiffies(MLX5_FPGA_LOAD_TIMEOUT);
	err = wait_for_completion_timeout(&fdev->load_event, timeout - jiffies);
	if (err < 0) {
		mlx5_fpga_err(fdev, "Failed waiting for FPGA load: %d\n", err);
		fdev->fdev_state = MLX5_FDEV_STATE_FAILURE;
		goto out;
	}

	err = mlx5_fpga_device_start(mdev);
	if (err) {
		mlx5_core_err(mdev, "fpga device start failed %d\n", err);
		goto out;
	}
	/* XXXKIB err = mlx5_accel_ipsec_init(mdev); */
	if (err) {
		mlx5_core_err(mdev, "IPSec device start failed %d\n", err);
		goto err_fpga;
	}

	err = mlx5_register_device(mdev);
	if (err) {
		mlx5_core_err(mdev, "mlx5_register_device failed %d\n", err);
		fdev->fdev_state = MLX5_FDEV_STATE_FAILURE;
		goto err_ipsec;
	}

	set_bit(MLX5_INTERFACE_STATE_UP, &mdev->intf_state);
	goto out;

err_ipsec:
	/* XXXKIB mlx5_accel_ipsec_cleanup(mdev); */
err_fpga:
	mlx5_fpga_device_stop(mdev);
out:
	mutex_unlock(&mdev->intf_state_mutex);
	return err;
}