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
struct mlx5_ib_qp {int dummy; } ;
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct mlx5_ib_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  mcq; int /*<<< orphan*/  wc_list; TYPE_1__ ibcq; } ;
struct mlx5_core_dev {scalar_t__ state; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cq_set_ci (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_poll_sw_comp (struct mlx5_ib_cq*,int,struct ib_wc*,int*) ; 
 scalar_t__ mlx5_poll_one (struct mlx5_ib_cq*,struct mlx5_ib_qp**,struct ib_wc*) ; 
 int poll_soft_wc (struct mlx5_ib_cq*,int,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mlx5_ib_cq* to_mcq (struct ib_cq*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int mlx5_ib_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct mlx5_ib_cq *cq = to_mcq(ibcq);
	struct mlx5_ib_qp *cur_qp = NULL;
	struct mlx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	struct mlx5_core_dev *mdev = dev->mdev;
	unsigned long flags;
	int soft_polled = 0;
	int npolled;

	spin_lock_irqsave(&cq->lock, flags);
	if (unlikely(mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)) {
		mlx5_ib_poll_sw_comp(cq, num_entries, wc, &npolled);
		goto out;
	}

	if (unlikely(!list_empty(&cq->wc_list)))
		soft_polled = poll_soft_wc(cq, num_entries, wc);

	for (npolled = 0; npolled < num_entries - soft_polled; npolled++) {
		if (mlx5_poll_one(cq, &cur_qp, wc + soft_polled + npolled))
			break;
	}

	if (npolled)
		mlx5_cq_set_ci(&cq->mcq);
out:
	spin_unlock_irqrestore(&cq->lock, flags);

	return soft_polled + npolled;
}