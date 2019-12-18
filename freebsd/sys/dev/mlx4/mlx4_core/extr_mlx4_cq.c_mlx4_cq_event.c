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
typedef  int u32 ;
struct TYPE_3__ {int num_cqs; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cq_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx4_cq {int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; int /*<<< orphan*/  (* event ) (struct mlx4_cq*,int) ;} ;
struct TYPE_4__ {struct mlx4_cq_table cq_table; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int) ; 
 struct mlx4_cq* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlx4_cq*,int) ; 

void mlx4_cq_event(struct mlx4_dev *dev, u32 cqn, int event_type)
{
	struct mlx4_cq_table *cq_table = &mlx4_priv(dev)->cq_table;
	struct mlx4_cq *cq;

	spin_lock(&cq_table->lock);

	cq = radix_tree_lookup(&cq_table->tree, cqn & (dev->caps.num_cqs - 1));
	if (cq)
		atomic_inc(&cq->refcount);

	spin_unlock(&cq_table->lock);

	if (!cq) {
		mlx4_warn(dev, "Async event for bogus CQ %08x\n", cqn);
		return;
	}

	cq->event(cq, event_type);

	if (atomic_dec_and_test(&cq->refcount))
		complete(&cq->free);
}