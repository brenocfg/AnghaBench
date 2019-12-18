#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  complete; TYPE_1__* sg; } ;
typedef  TYPE_2__ u32 ;
struct mlx5_fpga_transaction {int size; scalar_t__ direction; TYPE_2__* data; int /*<<< orphan*/  addr; int /*<<< orphan*/  complete1; struct mlx5_fpga_conn* conn; } ;
struct mlx5_fpga_trans_priv {int tid; TYPE_2__ buf; int /*<<< orphan*/  state; TYPE_2__* header; struct mlx5_fpga_transaction const* user_trans; } ;
struct mlx5_fpga_conn {TYPE_3__* fdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  shell_conn; } ;
struct TYPE_11__ {int size; TYPE_2__* data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_READ ; 
 int MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_WRITE ; 
 scalar_t__ MLX5_FPGA_WRITE ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_STATE_SEND ; 
 int /*<<< orphan*/  address ; 
 struct mlx5_fpga_trans_priv* alloc_tid (TYPE_3__*) ; 
 int /*<<< orphan*/  fpga_shell_qp_packet ; 
 int /*<<< orphan*/  free_tid (TYPE_3__*,struct mlx5_fpga_trans_priv*) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int mlx5_fpga_conn_send (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  tid ; 
 int /*<<< orphan*/  trans_send_complete ; 
 int trans_validate (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  type ; 

int mlx5_fpga_trans_exec(const struct mlx5_fpga_transaction *trans)
{
	struct mlx5_fpga_conn *conn = trans->conn;
	struct mlx5_fpga_trans_priv *trans_priv;
	u32 *header;
	int err;

	if (!trans->complete1) {
		mlx5_fpga_warn(conn->fdev, "Transaction must have a completion callback\n");
		err = -EINVAL;
		goto out;
	}

	err = trans_validate(conn->fdev, trans->addr, trans->size);
	if (err)
		goto out;

	trans_priv = alloc_tid(conn->fdev);
	if (!trans_priv) {
		err = -EBUSY;
		goto out;
	}
	trans_priv->user_trans = trans;
	header = trans_priv->header;

	memset(header, 0, sizeof(trans_priv->header));
	memset(&trans_priv->buf, 0, sizeof(trans_priv->buf));
	MLX5_SET(fpga_shell_qp_packet, header, type,
		 (trans->direction == MLX5_FPGA_WRITE) ?
		 MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_WRITE :
		 MLX5_FPGA_SHELL_QP_PACKET_TYPE_DDR_READ);
	MLX5_SET(fpga_shell_qp_packet, header, tid, trans_priv->tid);
	MLX5_SET(fpga_shell_qp_packet, header, len, trans->size);
	MLX5_SET64(fpga_shell_qp_packet, header, address, trans->addr);

	trans_priv->buf.sg[0].data = header;
	trans_priv->buf.sg[0].size = sizeof(trans_priv->header);
	if (trans->direction == MLX5_FPGA_WRITE) {
		trans_priv->buf.sg[1].data = trans->data;
		trans_priv->buf.sg[1].size = trans->size;
	}

	trans_priv->buf.complete = trans_send_complete;
	trans_priv->state = TRANS_STATE_SEND;

#ifdef NOT_YET
	/* XXXKIB */
	err = mlx5_fpga_conn_send(conn->fdev->shell_conn, &trans_priv->buf);
#else
	err = 0;
#endif
	if (err)
		goto out_buf_tid;
	goto out;

out_buf_tid:
	free_tid(conn->fdev, trans_priv);
out:
	return err;
}