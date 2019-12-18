#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fpga_device {struct mlx5_core_dev* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mqp; } ;
struct mlx5_fpga_conn {TYPE_1__ qp; int /*<<< orphan*/  fpga_qpc; struct mlx5_fpga_device* fdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ack_timeout; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_CMD_OP_RTR2RTS_QP ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_QP_OPTPAR_RNR_TIMEOUT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpga_qpc ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_ack_req_freq ; 
 int /*<<< orphan*/  min_rnr_nak ; 
 int mlx5_core_qp_modify (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int) ; 
 int /*<<< orphan*/  next_rcv_psn ; 
 int /*<<< orphan*/  next_send_psn ; 
 TYPE_2__ primary_address_path ; 
 int /*<<< orphan*/  retry_count ; 
 int /*<<< orphan*/  rnr_retry ; 

__attribute__((used)) static inline int mlx5_fpga_conn_rts_qp(struct mlx5_fpga_conn *conn)
{
	struct mlx5_fpga_device *fdev = conn->fdev;
	struct mlx5_core_dev *mdev = fdev->mdev;
	u32 *qpc = NULL;
	u32 opt_mask;
	int err;

	mlx5_fpga_dbg(conn->fdev, "QP RTS\n");

	qpc = kzalloc(MLX5_ST_SZ_BYTES(qpc), GFP_KERNEL);
	if (!qpc) {
		err = -ENOMEM;
		goto out;
	}

	MLX5_SET(qpc, qpc, log_ack_req_freq, 8);
	MLX5_SET(qpc, qpc, min_rnr_nak, 0x12);
	MLX5_SET(qpc, qpc, primary_address_path.ack_timeout, 0x12); /* ~1.07s */
	MLX5_SET(qpc, qpc, next_send_psn,
		 MLX5_GET(fpga_qpc, conn->fpga_qpc, next_rcv_psn));
	MLX5_SET(qpc, qpc, retry_count, 7);
	MLX5_SET(qpc, qpc, rnr_retry, 7); /* Infinite retry if RNR NACK */

	opt_mask = MLX5_QP_OPTPAR_RNR_TIMEOUT;
	err = mlx5_core_qp_modify(mdev, MLX5_CMD_OP_RTR2RTS_QP, opt_mask, qpc,
				  &conn->qp.mqp);
	if (err) {
		mlx5_fpga_warn(fdev, "qp_modify RST2INIT failed: %d\n", err);
		goto out;
	}

out:
	kfree(qpc);
	return err;
}