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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fpga_device {struct mlx5_core_dev* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mqp; int /*<<< orphan*/  sgid_index; } ;
struct mlx5_fpga_conn {TYPE_1__ qp; int /*<<< orphan*/ * fpga_qpc; int /*<<< orphan*/  fpga_qpn; struct mlx5_fpga_device* fdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rgid_rip; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  src_addr_index; int /*<<< orphan*/  udp_sport; int /*<<< orphan*/  rmac_47_32; int /*<<< orphan*/  port; int /*<<< orphan*/  pkey_index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_ADDR_OF (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_ROCE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CMD_OP_INIT2RTR_QP ; 
 int /*<<< orphan*/  MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FPGA_PKEY_INDEX ; 
 int /*<<< orphan*/  MLX5_FPGA_PORT_NUM ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_QPC_MTU_1K_BYTES ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_ip ; 
 int /*<<< orphan*/  fpga_mac_47_32 ; 
 int /*<<< orphan*/ * fpga_qpc ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_msg ; 
 int /*<<< orphan*/  log_msg_max ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_core_qp_modify (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int) ; 
 int /*<<< orphan*/  mtu ; 
 int /*<<< orphan*/  next_rcv_psn ; 
 int /*<<< orphan*/  next_send_psn ; 
 TYPE_2__ primary_address_path ; 
 int /*<<< orphan*/  r_roce_min_src_udp_port ; 
 int /*<<< orphan*/  remote_qpn ; 

__attribute__((used)) static inline int mlx5_fpga_conn_rtr_qp(struct mlx5_fpga_conn *conn)
{
	struct mlx5_fpga_device *fdev = conn->fdev;
	struct mlx5_core_dev *mdev = fdev->mdev;
	u32 *qpc = NULL;
	int err;

	mlx5_fpga_dbg(conn->fdev, "QP RTR\n");

	qpc = kzalloc(MLX5_ST_SZ_BYTES(qpc), GFP_KERNEL);
	if (!qpc) {
		err = -ENOMEM;
		goto out;
	}

	MLX5_SET(qpc, qpc, mtu, MLX5_QPC_MTU_1K_BYTES);
	MLX5_SET(qpc, qpc, log_msg_max, (u8)MLX5_CAP_GEN(mdev, log_max_msg));
	MLX5_SET(qpc, qpc, remote_qpn, conn->fpga_qpn);
	MLX5_SET(qpc, qpc, next_rcv_psn,
		 MLX5_GET(fpga_qpc, conn->fpga_qpc, next_send_psn));
	MLX5_SET(qpc, qpc, primary_address_path.pkey_index, MLX5_FPGA_PKEY_INDEX);
	MLX5_SET(qpc, qpc, primary_address_path.port, MLX5_FPGA_PORT_NUM);
	ether_addr_copy(MLX5_ADDR_OF(qpc, qpc, primary_address_path.rmac_47_32),
			MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, fpga_mac_47_32));
	MLX5_SET(qpc, qpc, primary_address_path.udp_sport,
		 MLX5_CAP_ROCE(mdev, r_roce_min_src_udp_port));
	MLX5_SET(qpc, qpc, primary_address_path.src_addr_index,
		 conn->qp.sgid_index);
	MLX5_SET(qpc, qpc, primary_address_path.hop_limit, 0);
	memcpy(MLX5_ADDR_OF(qpc, qpc, primary_address_path.rgid_rip),
	       MLX5_ADDR_OF(fpga_qpc, conn->fpga_qpc, fpga_ip),
	       MLX5_FLD_SZ_BYTES(qpc, primary_address_path.rgid_rip));

	err = mlx5_core_qp_modify(mdev, MLX5_CMD_OP_INIT2RTR_QP, 0, qpc,
				  &conn->qp.mqp);
	if (err) {
		mlx5_fpga_warn(fdev, "qp_modify RST2INIT failed: %d\n", err);
		goto out;
	}

out:
	kfree(qpc);
	return err;
}