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
struct mlx4_ib_qp {int port; TYPE_2__* counter_index; } ;
struct mlx4_ib_dev {TYPE_1__* counters_table; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_counter_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_ib_free_qp_counter(struct mlx4_ib_dev *dev,
				    struct mlx4_ib_qp *qp)
{
	mutex_lock(&dev->counters_table[qp->port - 1].mutex);
	mlx4_counter_free(dev->dev, qp->counter_index->index);
	list_del(&qp->counter_index->list);
	mutex_unlock(&dev->counters_table[qp->port - 1].mutex);

	kfree(qp->counter_index);
	qp->counter_index = NULL;
}