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
typedef  int u8 ;
struct mlx5_fpga_trans_priv {TYPE_1__* user_trans; } ;
struct mlx5_fpga_dma_buf {TYPE_2__* sg; } ;
struct mlx5_fpga_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {size_t direction; size_t size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MLX5_FPGA_READ ; 
#define  MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_READ_RESPONSE 129 
#define  MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_WRITE_RESPONSE 128 
 size_t MLX5_FPGA_WRITE ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 struct mlx5_fpga_trans_priv* find_tid (struct mlx5_fpga_device*,int) ; 
 int /*<<< orphan*/  fpga_shell_qp_packet ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int,...) ; 
 int /*<<< orphan*/  trans_complete (struct mlx5_fpga_device*,struct mlx5_fpga_trans_priv*,int) ; 

void mlx5_fpga_trans_recv(void *cb_arg, struct mlx5_fpga_dma_buf *buf)
{
	struct mlx5_fpga_device *fdev = cb_arg;
	struct mlx5_fpga_trans_priv *trans_priv;
	size_t payload_len;
	u8 status = 0;
	u8 tid, type;

	mlx5_fpga_dbg(fdev, "Rx QP message on core conn; %u bytes\n",
		      buf->sg[0].size);

	if (buf->sg[0].size < MLX5_ST_SZ_BYTES(fpga_shell_qp_packet)) {
		mlx5_fpga_warn(fdev, "Short message %u bytes from device\n",
			       buf->sg[0].size);
		goto out;
	}
	payload_len = buf->sg[0].size - MLX5_ST_SZ_BYTES(fpga_shell_qp_packet);

	tid = MLX5_GET(fpga_shell_qp_packet, buf->sg[0].data, tid);
	trans_priv = find_tid(fdev, tid);
	if (!trans_priv)
		goto out;

	type = MLX5_GET(fpga_shell_qp_packet, buf->sg[0].data, type);
	switch (type) {
	case MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_READ_RESPONSE:
		if (trans_priv->user_trans->direction != MLX5_FPGA_READ) {
			mlx5_fpga_warn(fdev, "Wrong answer type %u to a %u transaction\n",
				       type, trans_priv->user_trans->direction);
			status = -EIO;
			goto complete;
		}
		if (payload_len != trans_priv->user_trans->size) {
			mlx5_fpga_warn(fdev, "Incorrect transaction payload length %zu expected %zu\n",
				       payload_len,
				       trans_priv->user_trans->size);
			goto complete;
		}
		memcpy(trans_priv->user_trans->data,
		       MLX5_ADDR_OF(fpga_shell_qp_packet, buf->sg[0].data,
				    data), payload_len);
		break;
	case MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_WRITE_RESPONSE:
		if (trans_priv->user_trans->direction != MLX5_FPGA_WRITE) {
			mlx5_fpga_warn(fdev, "Wrong answer type %u to a %u transaction\n",
				       type, trans_priv->user_trans->direction);
			status = -EIO;
			goto complete;
		}
		break;
	default:
		mlx5_fpga_warn(fdev, "Unexpected message type %u len %u from device\n",
			       type, buf->sg[0].size);
		status = -EIO;
		goto complete;
	}

complete:
	trans_complete(fdev, trans_priv, status);
out:
	return;
}