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
struct mlx5_ib_mr {int /*<<< orphan*/  mmkey; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mr_srcu; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5_core_destroy_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int destroy_mkey(struct mlx5_ib_dev *dev, struct mlx5_ib_mr *mr)
{
	int err = mlx5_core_destroy_mkey(dev->mdev, &mr->mmkey);

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	/* Wait until all page fault handlers using the mr complete. */
	synchronize_srcu(&dev->mr_srcu);
#endif

	return err;
}