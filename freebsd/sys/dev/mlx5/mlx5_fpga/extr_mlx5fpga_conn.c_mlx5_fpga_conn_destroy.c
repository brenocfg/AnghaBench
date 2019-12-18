#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_fpga_device {struct mlx5_core_dev* mdev; } ;
struct TYPE_6__ {int active; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  mqp; } ;
struct TYPE_4__ {int /*<<< orphan*/  irqn; } ;
struct TYPE_5__ {TYPE_1__ mcq; int /*<<< orphan*/  tasklet; } ;
struct mlx5_fpga_conn {TYPE_3__ qp; struct mlx5_fpga_device* fdev; int /*<<< orphan*/  fpga_qpn; TYPE_2__ cq; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CMD_OP_2ERR_QP ; 
 int /*<<< orphan*/  kfree (struct mlx5_fpga_conn*) ; 
 int mlx5_core_qp_modify (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_reserved_gid_free (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_roce_gid_set (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_destroy_cq (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_destroy_qp (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_fpga_destroy_qp (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

void mlx5_fpga_conn_destroy(struct mlx5_fpga_conn *conn)
{
	struct mlx5_fpga_device *fdev = conn->fdev;
	struct mlx5_core_dev *mdev = fdev->mdev;
	int err = 0;

	conn->qp.active = false;
	tasklet_disable(&conn->cq.tasklet);
	synchronize_irq(conn->cq.mcq.irqn);

	mlx5_fpga_destroy_qp(conn->fdev->mdev, conn->fpga_qpn);
	err = mlx5_core_qp_modify(mdev, MLX5_CMD_OP_2ERR_QP, 0, NULL,
				  &conn->qp.mqp);
	if (err)
		mlx5_fpga_warn(fdev, "qp_modify 2ERR failed: %d\n", err);
	mlx5_fpga_conn_destroy_qp(conn);
	mlx5_fpga_conn_destroy_cq(conn);

	mlx5_core_roce_gid_set(conn->fdev->mdev, conn->qp.sgid_index, 0, 0,
			       NULL, NULL, false, 0);
	mlx5_core_reserved_gid_free(conn->fdev->mdev, conn->qp.sgid_index);
	kfree(conn);
}