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
typedef  int uint32_t ;
struct mlx5_crspace_regmap {scalar_t__ cnt; scalar_t__ addr; } ;
struct mlx5_core_dev {int dump_valid; int /*<<< orphan*/  dump_lock; int /*<<< orphan*/ * dump_data; struct mlx5_crspace_regmap* dump_rege; } ;

/* Variables and functions */
 int EEXIST ; 
 int EIO ; 
 int /*<<< orphan*/  MLX5_VSC_DOMAIN_PROTECTED_CRSPACE ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int mlx5_vsc_lock (struct mlx5_core_dev*) ; 
 int mlx5_vsc_read (struct mlx5_core_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int mlx5_vsc_set_space (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_vsc_unlock (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
mlx5_fwdump(struct mlx5_core_dev *mdev)
{
	const struct mlx5_crspace_regmap *r;
	uint32_t i, ri;
	int error;

	mlx5_core_info(mdev, "Issuing FW dump\n");
	mtx_lock(&mdev->dump_lock);
	if (mdev->dump_data == NULL) {
		error = EIO;
		goto failed;
	}
	if (mdev->dump_valid) {
		/* only one dump */
		mlx5_core_warn(mdev,
		    "Only one FW dump can be captured aborting FW dump\n");
		error = EEXIST;
		goto failed;
	}

	/* mlx5_vsc already warns, be silent. */
	error = mlx5_vsc_lock(mdev);
	if (error != 0)
		goto failed;
	error = mlx5_vsc_set_space(mdev, MLX5_VSC_DOMAIN_PROTECTED_CRSPACE);
	if (error != 0)
		goto unlock_vsc;
	for (i = 0, r = mdev->dump_rege; r->cnt != 0; r++) {
		for (ri = 0; ri < r->cnt; ri++) {
			error = mlx5_vsc_read(mdev, r->addr + ri * 4,
			    &mdev->dump_data[i]);
			if (error != 0)
				goto unlock_vsc;
			i++;
		}
	}
	mdev->dump_valid = true;
unlock_vsc:
	mlx5_vsc_unlock(mdev);
failed:
	mtx_unlock(&mdev->dump_lock);
	return (error);
}