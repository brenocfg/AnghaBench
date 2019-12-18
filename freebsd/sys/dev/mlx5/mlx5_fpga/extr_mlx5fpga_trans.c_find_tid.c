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
typedef  size_t u8 ;
struct mlx5_fpga_trans_priv {int dummy; } ;
struct mlx5_fpga_device {TYPE_1__* trans; } ;
struct TYPE_2__ {struct mlx5_fpga_trans_priv* transactions; } ;

/* Variables and functions */
 size_t MLX5_FPGA_TID_COUNT ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,size_t) ; 

__attribute__((used)) static struct mlx5_fpga_trans_priv *find_tid(struct mlx5_fpga_device *fdev,
					     u8 tid)
{
	if (tid >= MLX5_FPGA_TID_COUNT) {
		mlx5_fpga_warn(fdev, "Unexpected transaction ID %u\n", tid);
		return NULL;
	}
	return &fdev->trans->transactions[tid];
}