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
struct mlx5_fpga_device {int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int active; } ;
struct mlx5_fpga_conn {int /*<<< orphan*/  fpga_qpc; int /*<<< orphan*/  fpga_qpn; struct mlx5_fpga_device* fdev; TYPE_1__ qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FPGA_QPC_STATE ; 
 int /*<<< orphan*/  MLX5_FPGA_QPC_STATE_ACTIVE ; 
 int /*<<< orphan*/  MLX5_FPGA_QPC_STATE_INIT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_qpc ; 
 int /*<<< orphan*/  mlx5_fpga_conn_free_recv_bufs (struct mlx5_fpga_conn*) ; 
 int mlx5_fpga_conn_init_qp (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_post_recv_buf (struct mlx5_fpga_conn*) ; 
 int mlx5_fpga_conn_reset_qp (struct mlx5_fpga_conn*) ; 
 int mlx5_fpga_conn_rtr_qp (struct mlx5_fpga_conn*) ; 
 int mlx5_fpga_conn_rts_qp (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,...) ; 
 int mlx5_fpga_modify_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state ; 

__attribute__((used)) static int mlx5_fpga_conn_connect(struct mlx5_fpga_conn *conn)
{
	struct mlx5_fpga_device *fdev = conn->fdev;
	int err;

	MLX5_SET(fpga_qpc, conn->fpga_qpc, state, MLX5_FPGA_QPC_STATE_ACTIVE);
	err = mlx5_fpga_modify_qp(conn->fdev->mdev, conn->fpga_qpn,
				  MLX5_FPGA_QPC_STATE, &conn->fpga_qpc);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to activate FPGA RC QP: %d\n", err);
		goto out;
	}

	err = mlx5_fpga_conn_reset_qp(conn);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to change QP state to reset\n");
		goto err_fpga_qp;
	}

	err = mlx5_fpga_conn_init_qp(conn);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to modify QP from RESET to INIT\n");
		goto err_fpga_qp;
	}
	conn->qp.active = true;

	while (!mlx5_fpga_conn_post_recv_buf(conn))
		;

	err = mlx5_fpga_conn_rtr_qp(conn);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to change QP state from INIT to RTR\n");
		goto err_recv_bufs;
	}

	err = mlx5_fpga_conn_rts_qp(conn);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to change QP state from RTR to RTS\n");
		goto err_recv_bufs;
	}
	goto out;

err_recv_bufs:
	mlx5_fpga_conn_free_recv_bufs(conn);
err_fpga_qp:
	MLX5_SET(fpga_qpc, conn->fpga_qpc, state, MLX5_FPGA_QPC_STATE_INIT);
	if (mlx5_fpga_modify_qp(conn->fdev->mdev, conn->fpga_qpn,
				MLX5_FPGA_QPC_STATE, &conn->fpga_qpc))
		mlx5_fpga_err(fdev, "Failed to revert FPGA QP to INIT\n");
out:
	return err;
}