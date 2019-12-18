#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_ib_mr {int npages; scalar_t__ live; struct ib_umem* umem; } ;
struct mlx5_ib_dev {TYPE_2__* mdev; int /*<<< orphan*/  mr_srcu; } ;
struct ib_umem {scalar_t__ odp_data; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_pages; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_mr (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  ib_umem_end (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_release (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_start (struct ib_umem*) ; 
 int /*<<< orphan*/  mlx5_ib_invalidate_range (struct ib_umem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mr* to_mmr (struct ib_mr*) ; 

int mlx5_ib_dereg_mr(struct ib_mr *ibmr)
{
	struct mlx5_ib_dev *dev = to_mdev(ibmr->device);
	struct mlx5_ib_mr *mr = to_mmr(ibmr);
	int npages = mr->npages;
	struct ib_umem *umem = mr->umem;

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	if (umem && umem->odp_data) {
		/* Prevent new page faults from succeeding */
		mr->live = 0;
		/* Wait for all running page-fault handlers to finish. */
		synchronize_srcu(&dev->mr_srcu);
		/* Destroy all page mappings */
		mlx5_ib_invalidate_range(umem, ib_umem_start(umem),
					 ib_umem_end(umem));
		/*
		 * We kill the umem before the MR for ODP,
		 * so that there will not be any invalidations in
		 * flight, looking at the *mr struct.
		 */
		ib_umem_release(umem);
		atomic_sub(npages, &dev->mdev->priv.reg_pages);

		/* Avoid double-freeing the umem. */
		umem = NULL;
	}
#endif

	clean_mr(mr);

	if (umem) {
		ib_umem_release(umem);
		atomic_sub(npages, &dev->mdev->priv.reg_pages);
	}

	return 0;
}