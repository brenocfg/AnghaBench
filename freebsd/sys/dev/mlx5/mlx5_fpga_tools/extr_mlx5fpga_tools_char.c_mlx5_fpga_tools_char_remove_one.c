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
struct mlx5_fpga_tools_dev {scalar_t__ char_device; int /*<<< orphan*/  fdev; } ;
struct cdev {int /*<<< orphan*/  si_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_dev (int /*<<< orphan*/ ) ; 

void mlx5_fpga_tools_char_remove_one(struct mlx5_fpga_tools_dev *tdev)
{

	dev_err(mlx5_fpga_dev(tdev->fdev), "tools char device %s destroyed\n",
	    ((struct cdev *)(tdev->char_device))->si_name);
	destroy_dev((struct cdev *)(tdev->char_device));
}