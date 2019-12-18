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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ u64 ;
struct mlx5_fpga_tools_dev {int /*<<< orphan*/  fdev; int /*<<< orphan*/  lock; } ;
typedef  enum mlx5_fpga_access_type { ____Placeholder_mlx5_fpga_access_type } mlx5_fpga_access_type ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fpga_dev (int /*<<< orphan*/ ) ; 
 int mlx5_fpga_mem_read (int /*<<< orphan*/ ,size_t,scalar_t__,void*,int) ; 
 int sx_xlock_sig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mem_read(struct mlx5_fpga_tools_dev *tdev, void *buf, size_t count,
    u64 address, enum mlx5_fpga_access_type access_type, size_t *retcnt)
{
	int ret;

	ret = sx_xlock_sig(&tdev->lock);
	if (ret != 0)
		return (ret);
	ret = mlx5_fpga_mem_read(tdev->fdev, count, address, buf, access_type);
	sx_xunlock(&tdev->lock);
	if (ret < 0) {
		dev_dbg(mlx5_fpga_dev(tdev->fdev),
			"Failed to read %zu bytes at address 0x%jx: %d\n",
			count, (uintmax_t)address, ret);
		return (-ret);
	}
	*retcnt = ret;
	return (0);
}