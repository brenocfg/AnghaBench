#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_fpga_tools_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_fpga_tools_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_tools_char_remove_one (struct mlx5_fpga_tools_dev*) ; 

void mlx5_fpga_tools_free(struct mlx5_fpga_tools_dev *tdev)
{
	mlx5_fpga_tools_char_remove_one(tdev);
	kfree(tdev);
}