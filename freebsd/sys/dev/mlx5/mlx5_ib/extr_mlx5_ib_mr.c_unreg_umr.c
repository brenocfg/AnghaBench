#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct umr_common {int /*<<< orphan*/  sem; int /*<<< orphan*/  qp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * wr_cqe; } ;
struct mlx5_umr_wr {TYPE_2__ wr; } ;
struct mlx5_ib_umr_context {scalar_t__ status; int /*<<< orphan*/  done; int /*<<< orphan*/  cqe; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct mlx5_ib_mr {TYPE_1__ mmkey; } ;
struct mlx5_ib_dev {struct umr_common umrc; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {scalar_t__ state; } ;
struct ib_send_wr {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_2__*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_ib_init_umr_context (struct mlx5_ib_umr_context*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 
 int /*<<< orphan*/  prep_umr_unreg_wqe (struct mlx5_ib_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unreg_umr(struct mlx5_ib_dev *dev, struct mlx5_ib_mr *mr)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	struct umr_common *umrc = &dev->umrc;
	struct mlx5_ib_umr_context umr_context;
	struct mlx5_umr_wr umrwr = {};
	struct ib_send_wr *bad;
	int err;

	if (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		return 0;

	mlx5_ib_init_umr_context(&umr_context);

	umrwr.wr.wr_cqe = &umr_context.cqe;
	prep_umr_unreg_wqe(dev, &umrwr.wr, mr->mmkey.key);

	down(&umrc->sem);
	err = ib_post_send(umrc->qp, &umrwr.wr, &bad);
	if (err) {
		up(&umrc->sem);
		mlx5_ib_dbg(dev, "err %d\n", err);
		goto error;
	} else {
		wait_for_completion(&umr_context.done);
		up(&umrc->sem);
	}
	if (umr_context.status != IB_WC_SUCCESS) {
		mlx5_ib_warn(dev, "unreg umr failed\n");
		err = -EFAULT;
		goto error;
	}
	return 0;

error:
	return err;
}