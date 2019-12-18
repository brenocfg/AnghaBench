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
struct TYPE_4__ {int max; int wqe_shift; } ;
struct mlx4_ib_srq {int /*<<< orphan*/  db; int /*<<< orphan*/  buf; TYPE_2__ msrq; int /*<<< orphan*/  wrid; int /*<<< orphan*/  umem; int /*<<< orphan*/  mtt; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_srq {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_srq*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_buf_free (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_db_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_db_unmap_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_srq_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_srq* to_msrq (struct ib_srq*) ; 
 int /*<<< orphan*/  to_mucontext (int /*<<< orphan*/ ) ; 

int mlx4_ib_destroy_srq(struct ib_srq *srq)
{
	struct mlx4_ib_dev *dev = to_mdev(srq->device);
	struct mlx4_ib_srq *msrq = to_msrq(srq);

	mlx4_srq_free(dev->dev, &msrq->msrq);
	mlx4_mtt_cleanup(dev->dev, &msrq->mtt);

	if (srq->uobject) {
		mlx4_ib_db_unmap_user(to_mucontext(srq->uobject->context), &msrq->db);
		ib_umem_release(msrq->umem);
	} else {
		kvfree(msrq->wrid);
		mlx4_buf_free(dev->dev, msrq->msrq.max << msrq->msrq.wqe_shift,
			      &msrq->buf);
		mlx4_db_free(dev->dev, &msrq->db);
	}

	kfree(msrq);

	return 0;
}