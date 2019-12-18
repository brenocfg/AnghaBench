#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_fpga_device {TYPE_1__* ipsec; } ;
struct mlx5_fpga_conn_attr {struct mlx5_fpga_device* cb_arg; int /*<<< orphan*/  recv_cb; void* tx_size; void* rx_size; int /*<<< orphan*/  member_0; } ;
struct mlx5_fpga_conn {int dummy; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;
struct TYPE_3__ {struct mlx5_fpga_conn* conn; int /*<<< orphan*/  pending_cmds_lock; int /*<<< orphan*/  pending_cmds; int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct mlx5_fpga_conn*) ; 
 int PTR_ERR (struct mlx5_fpga_conn*) ; 
 void* SBU_QP_QUEUE_SIZE ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int) ; 
 int mlx5_fpga_get_sbu_caps (struct mlx5_fpga_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_recv ; 
 int /*<<< orphan*/  mlx5_fpga_is_ipsec_device (struct mlx5_core_dev*) ; 
 struct mlx5_fpga_conn* mlx5_fpga_sbu_conn_create (struct mlx5_fpga_device*,struct mlx5_fpga_conn_attr*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5_fpga_ipsec_init(struct mlx5_core_dev *mdev)
{
	struct mlx5_fpga_conn_attr init_attr = {0};
	struct mlx5_fpga_device *fdev = mdev->fpga;
	struct mlx5_fpga_conn *conn;
	int err;

	if (!mlx5_fpga_is_ipsec_device(mdev))
		return 0;

	fdev->ipsec = kzalloc(sizeof(*fdev->ipsec), GFP_KERNEL);
	if (!fdev->ipsec)
		return -ENOMEM;

	err = mlx5_fpga_get_sbu_caps(fdev, sizeof(fdev->ipsec->caps),
				     fdev->ipsec->caps);
	if (err) {
		mlx5_fpga_err(fdev, "Failed to retrieve IPSec extended capabilities: %d\n",
			      err);
		goto error;
	}

	INIT_LIST_HEAD(&fdev->ipsec->pending_cmds);
	spin_lock_init(&fdev->ipsec->pending_cmds_lock);

	init_attr.rx_size = SBU_QP_QUEUE_SIZE;
	init_attr.tx_size = SBU_QP_QUEUE_SIZE;
	init_attr.recv_cb = mlx5_fpga_ipsec_recv;
	init_attr.cb_arg = fdev;
	conn = mlx5_fpga_sbu_conn_create(fdev, &init_attr);
	if (IS_ERR(conn)) {
		err = PTR_ERR(conn);
		mlx5_fpga_err(fdev, "Error creating IPSec command connection %d\n",
			      err);
		goto error;
	}
	fdev->ipsec->conn = conn;
	return 0;

error:
	kfree(fdev->ipsec);
	fdev->ipsec = NULL;
	return err;
}