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
struct mlx5_fpga_dma_buf {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {scalar_t__ pc; scalar_t__ cc; scalar_t__ size; int /*<<< orphan*/  lock; int /*<<< orphan*/  backlog; } ;
struct TYPE_4__ {TYPE_1__ sq; int /*<<< orphan*/  active; } ;
struct mlx5_fpga_conn {TYPE_2__ qp; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlx5_fpga_conn_map_buf (struct mlx5_fpga_conn*,struct mlx5_fpga_dma_buf*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_post_send (struct mlx5_fpga_conn*,struct mlx5_fpga_dma_buf*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mlx5_fpga_conn_send(struct mlx5_fpga_conn *conn,
			struct mlx5_fpga_dma_buf *buf)
{
	unsigned long flags;
	int err;

	if (!conn->qp.active)
		return -ENOTCONN;

	err = mlx5_fpga_conn_map_buf(conn, buf);
	if (err)
		return err;

	spin_lock_irqsave(&conn->qp.sq.lock, flags);

	if (conn->qp.sq.pc - conn->qp.sq.cc >= conn->qp.sq.size) {
		list_add_tail(&buf->list, &conn->qp.sq.backlog);
		goto out_unlock;
	}

	mlx5_fpga_conn_post_send(conn, buf);

out_unlock:
	spin_unlock_irqrestore(&conn->qp.sq.lock, flags);
	return err;
}