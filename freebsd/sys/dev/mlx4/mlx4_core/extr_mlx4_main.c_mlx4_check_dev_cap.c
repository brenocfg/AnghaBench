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
struct mlx4_dev_cap {int flags2; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int MLX4_DEV_CAP_CHECK_NUM_VFS_ABOVE_64 ; 
 int MLX4_DEV_CAP_FLAG2_80_VFS ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int) ; 

__attribute__((used)) static int mlx4_check_dev_cap(struct mlx4_dev *dev, struct mlx4_dev_cap *dev_cap,
			      int *nvfs)
{
	int requested_vfs = nvfs[0] + nvfs[1] + nvfs[2];
	/* Checking for 64 VFs as a limitation of CX2 */
	if (!(dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_80_VFS) &&
	    requested_vfs >= 64) {
		mlx4_err(dev, "Requested %d VFs, but FW does not support more than 64\n",
			 requested_vfs);
		return MLX4_DEV_CAP_CHECK_NUM_VFS_ABOVE_64;
	}
	return 0;
}