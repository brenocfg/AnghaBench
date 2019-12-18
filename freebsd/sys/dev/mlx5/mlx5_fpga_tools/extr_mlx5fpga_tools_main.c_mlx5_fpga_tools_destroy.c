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
struct mlx5_fpga_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct mlx5_fpga_tools_dev* mlx5_fpga_client_data_get (struct mlx5_fpga_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fpga_dev (struct mlx5_fpga_device*) ; 
 int /*<<< orphan*/  mlx5_fpga_tools_client ; 
 int /*<<< orphan*/  mlx5_fpga_tools_free (struct mlx5_fpga_tools_dev*) ; 

__attribute__((used)) static void mlx5_fpga_tools_destroy(struct mlx5_fpga_device *fdev)
{
	struct mlx5_fpga_tools_dev *dev;

	dev_dbg(mlx5_fpga_dev(fdev), "tools_destroy\n");

	dev = mlx5_fpga_client_data_get(fdev, &mlx5_fpga_tools_client);
	if (dev)
		mlx5_fpga_tools_free(dev);
}