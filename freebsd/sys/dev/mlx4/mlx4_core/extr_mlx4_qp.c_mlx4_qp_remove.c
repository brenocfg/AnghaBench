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
struct mlx4_qp_table {int /*<<< orphan*/  lock; } ;
struct mlx4_qp {int qpn; } ;
struct TYPE_3__ {int num_qps; } ;
struct mlx4_dev {TYPE_1__ caps; int /*<<< orphan*/  qp_table_tree; } ;
struct TYPE_4__ {struct mlx4_qp_table qp_table; } ;

/* Variables and functions */
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mlx4_qp_remove(struct mlx4_dev *dev, struct mlx4_qp *qp)
{
	struct mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;
	unsigned long flags;

	spin_lock_irqsave(&qp_table->lock, flags);
	radix_tree_delete(&dev->qp_table_tree, qp->qpn & (dev->caps.num_qps - 1));
	spin_unlock_irqrestore(&qp_table->lock, flags);
}