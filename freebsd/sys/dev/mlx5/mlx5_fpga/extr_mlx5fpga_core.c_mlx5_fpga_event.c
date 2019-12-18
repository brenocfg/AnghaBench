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
typedef  int u8 ;
typedef  int u32 ;
struct mlx5_fpga_device {int fdev_state; int /*<<< orphan*/  mdev; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  load_event; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;

/* Variables and functions */
#define  MLX5_EVENT_TYPE_FPGA_ERROR 131 
#define  MLX5_EVENT_TYPE_FPGA_QP_ERROR 130 
#define  MLX5_FDEV_STATE_IN_PROGRESS 129 
#define  MLX5_FDEV_STATE_SUCCESS 128 
 int MLX5_FPGA_ERROR_EVENT_SYNDROME_IMAGE_CHANGED ; 
 int MLX5_GET (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpga_error_event ; 
 int /*<<< orphan*/  fpga_qp_error_event ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int,int,char const*) ; 
 char* mlx5_fpga_qp_syndrome_to_string (int) ; 
 char* mlx5_fpga_syndrome_to_string (int) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int,char const*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn_ratelimited (struct mlx5_fpga_device*,char*,int,...) ; 
 int /*<<< orphan*/  mlx5_trigger_health_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mlx5_fpga_event(struct mlx5_core_dev *mdev, u8 event, void *data)
{
	struct mlx5_fpga_device *fdev = mdev->fpga;
	const char *event_name;
	bool teardown = false;
	unsigned long flags;
	u32 fpga_qpn;
	u8 syndrome;

	switch (event) {
	case MLX5_EVENT_TYPE_FPGA_ERROR:
		syndrome = MLX5_GET(fpga_error_event, data, syndrome);
		event_name = mlx5_fpga_syndrome_to_string(syndrome);
		break;
	case MLX5_EVENT_TYPE_FPGA_QP_ERROR:
		syndrome = MLX5_GET(fpga_qp_error_event, data, syndrome);
		event_name = mlx5_fpga_qp_syndrome_to_string(syndrome);
		fpga_qpn = MLX5_GET(fpga_qp_error_event, data, fpga_qpn);
		mlx5_fpga_err(fdev, "Error %u on QP %u: %s\n",
			      syndrome, fpga_qpn, event_name);
		break;
	default:
		mlx5_fpga_warn_ratelimited(fdev, "Unexpected event %u\n",
					   event);
		return;
	}

	spin_lock_irqsave(&fdev->state_lock, flags);
	switch (fdev->fdev_state) {
	case MLX5_FDEV_STATE_SUCCESS:
		mlx5_fpga_warn(fdev, "Error %u: %s\n", syndrome, event_name);
		teardown = true;
		break;
	case MLX5_FDEV_STATE_IN_PROGRESS:
		if (syndrome != MLX5_FPGA_ERROR_EVENT_SYNDROME_IMAGE_CHANGED)
			mlx5_fpga_warn(fdev, "Error while loading %u: %s\n",
				       syndrome, event_name);
		complete(&fdev->load_event);
		break;
	default:
		mlx5_fpga_warn_ratelimited(fdev, "Unexpected error event %u: %s\n",
					   syndrome, event_name);
	}
	spin_unlock_irqrestore(&fdev->state_lock, flags);
	/* We tear-down the card's interfaces and functionality because
	 * the FPGA bump-on-the-wire is misbehaving and we lose ability
	 * to communicate with the network. User may still be able to
	 * recover by re-programming or debugging the FPGA
	 */
	if (teardown)
		mlx5_trigger_health_work(fdev->mdev);
}