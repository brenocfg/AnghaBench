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
struct mlx5_fpga_device {TYPE_1__* ipsec; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5_fpga_is_ipsec_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_sbu_conn_destroy (int /*<<< orphan*/ ) ; 

void mlx5_fpga_ipsec_cleanup(struct mlx5_core_dev *mdev)
{
	struct mlx5_fpga_device *fdev = mdev->fpga;

	if (!mlx5_fpga_is_ipsec_device(mdev))
		return;

	mlx5_fpga_sbu_conn_destroy(fdev->ipsec->conn);
	kfree(fdev->ipsec);
	fdev->ipsec = NULL;
}