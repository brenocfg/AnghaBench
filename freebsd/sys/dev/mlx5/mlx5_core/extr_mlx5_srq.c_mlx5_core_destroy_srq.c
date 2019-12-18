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
struct mlx5_srq_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx5_core_srq {int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; int /*<<< orphan*/  srqn; } ;
struct TYPE_2__ {struct mlx5_srq_table srq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int destroy_srq_split (struct mlx5_core_dev*,struct mlx5_core_srq*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 struct mlx5_core_srq* radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int mlx5_core_destroy_srq(struct mlx5_core_dev *dev, struct mlx5_core_srq *srq)
{
	struct mlx5_srq_table *table = &dev->priv.srq_table;
	struct mlx5_core_srq *tmp;
	int err;

	spin_lock_irq(&table->lock);
	tmp = radix_tree_delete(&table->tree, srq->srqn);
	spin_unlock_irq(&table->lock);
	if (!tmp) {
		mlx5_core_warn(dev, "srq 0x%x not found in tree\n", srq->srqn);
		return -EINVAL;
	}
	if (tmp != srq) {
		mlx5_core_warn(dev, "corruption on srqn 0x%x\n", srq->srqn);
		return -EINVAL;
	}

	err = destroy_srq_split(dev, srq);
	if (err)
		return err;

	if (atomic_dec_and_test(&srq->refcount))
		complete(&srq->free);
	wait_for_completion(&srq->free);

	return 0;
}