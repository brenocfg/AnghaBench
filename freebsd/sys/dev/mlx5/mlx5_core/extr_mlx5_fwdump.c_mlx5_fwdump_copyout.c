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
struct mlx5_fwdump_reg {int /*<<< orphan*/  val; scalar_t__ addr; } ;
struct mlx5_fwdump_get {int reg_filled; int reg_cnt; struct mlx5_fwdump_reg* buf; } ;
struct mlx5_crspace_regmap {scalar_t__ cnt; scalar_t__ addr; } ;
struct mlx5_core_dev {int dump_size; int dump_copyout; int /*<<< orphan*/  dump_lock; int /*<<< orphan*/ * dump_data; struct mlx5_crspace_regmap* dump_rege; int /*<<< orphan*/  dump_valid; } ;
typedef  int /*<<< orphan*/  rv ;

/* Variables and functions */
 int ENOENT ; 
 int copyout (struct mlx5_fwdump_reg*,struct mlx5_fwdump_reg*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static int
mlx5_fwdump_copyout(struct mlx5_core_dev *mdev, struct mlx5_fwdump_get *fwg)
{
	const struct mlx5_crspace_regmap *r;
	struct mlx5_fwdump_reg rv, *urv;
	uint32_t i, ri;
	int error;

	mtx_lock(&mdev->dump_lock);
	if (mdev->dump_data == NULL) {
		mtx_unlock(&mdev->dump_lock);
		return (ENOENT);
	}
	if (fwg->buf == NULL) {
		fwg->reg_filled = mdev->dump_size;
		mtx_unlock(&mdev->dump_lock);
		return (0);
	}
	if (!mdev->dump_valid) {
		mtx_unlock(&mdev->dump_lock);
		return (ENOENT);
	}
	mdev->dump_copyout = true;
	mtx_unlock(&mdev->dump_lock);

	urv = fwg->buf;
	for (i = 0, r = mdev->dump_rege; r->cnt != 0; r++) {
		for (ri = 0; ri < r->cnt; ri++) {
			if (i >= fwg->reg_cnt)
				goto out;
			rv.addr = r->addr + ri * 4;
			rv.val = mdev->dump_data[i];
			error = copyout(&rv, urv, sizeof(rv));
			if (error != 0)
				return (error);
			urv++;
			i++;
		}
	}
out:
	fwg->reg_filled = i;
	mtx_lock(&mdev->dump_lock);
	mdev->dump_copyout = false;
	wakeup(&mdev->dump_copyout);
	mtx_unlock(&mdev->dump_lock);
	return (0);
}