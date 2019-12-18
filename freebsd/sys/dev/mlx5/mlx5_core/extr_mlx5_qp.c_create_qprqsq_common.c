#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5_qp_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct TYPE_5__ {int res; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct mlx5_core_qp {int qpn; int /*<<< orphan*/  pid; TYPE_1__ common; } ;
struct TYPE_7__ {struct mlx5_qp_table qp_table; } ;
struct mlx5_core_dev {TYPE_3__ priv; } ;
struct TYPE_8__ {TYPE_2__* td_proc; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* curthread ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int,struct mlx5_core_qp*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_qprqsq_common(struct mlx5_core_dev *dev,
				struct mlx5_core_qp *qp, int rsc_type)
{
	struct mlx5_qp_table *table = &dev->priv.qp_table;
	int err;

	qp->common.res = rsc_type;

	spin_lock_irq(&table->lock);
	err = radix_tree_insert(&table->tree, qp->qpn | (rsc_type << 24), qp);
	spin_unlock_irq(&table->lock);
	if (err)
		return err;

	atomic_set(&qp->common.refcount, 1);
	init_completion(&qp->common.free);
	qp->pid = curthread->td_proc->p_pid;

	return 0;
}