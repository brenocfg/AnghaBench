#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_ib_srq {int /*<<< orphan*/  umem; int /*<<< orphan*/  db; int /*<<< orphan*/  msrq; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_srq {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_srq_kernel (struct mlx5_ib_dev*,struct mlx5_ib_srq*) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_srq*) ; 
 int /*<<< orphan*/  mlx5_core_destroy_srq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_srq* to_msrq (struct ib_srq*) ; 
 int /*<<< orphan*/  to_mucontext (int /*<<< orphan*/ ) ; 

int mlx5_ib_destroy_srq(struct ib_srq *srq)
{
	struct mlx5_ib_dev *dev = to_mdev(srq->device);
	struct mlx5_ib_srq *msrq = to_msrq(srq);

	mlx5_core_destroy_srq(dev->mdev, &msrq->msrq);

	if (srq->uobject) {
		mlx5_ib_db_unmap_user(to_mucontext(srq->uobject->context), &msrq->db);
		ib_umem_release(msrq->umem);
	} else {
		destroy_srq_kernel(dev, msrq);
	}

	kfree(srq);
	return 0;
}