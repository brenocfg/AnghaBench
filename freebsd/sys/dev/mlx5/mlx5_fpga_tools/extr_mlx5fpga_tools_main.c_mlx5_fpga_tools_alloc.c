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
struct mlx5_fpga_tools_dev {int /*<<< orphan*/  lock; struct mlx5_fpga_device* fdev; } ;
struct mlx5_fpga_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx5_fpga_tools_dev*) ; 
 struct mlx5_fpga_tools_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_fpga_tools_char_add_one (struct mlx5_fpga_tools_dev*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

struct mlx5_fpga_tools_dev *mlx5_fpga_tools_alloc(struct mlx5_fpga_device *fdev)
{
	int ret;
	struct mlx5_fpga_tools_dev *tdev;

	tdev = kzalloc(sizeof(*tdev), GFP_KERNEL);
	if (!tdev)
		goto out;

	tdev->fdev = fdev;
	sx_init(&tdev->lock, "mlx5fpgat");
	ret = mlx5_fpga_tools_char_add_one(tdev);
	if (ret)
		goto err_free;

	goto out;

err_free:
	kfree(tdev);
	tdev = NULL;

out:
	return tdev;
}