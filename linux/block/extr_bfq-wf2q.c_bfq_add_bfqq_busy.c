#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfq_queue {int ioprio_class; int wr_coeff; int /*<<< orphan*/  dispatched; } ;
struct bfq_data {int /*<<< orphan*/  wr_busy_queues; int /*<<< orphan*/  queue_weights_tree; int /*<<< orphan*/ * busy_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_activate_bfqq (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_busy (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_weights_tree_add (struct bfq_data*,struct bfq_queue*,int /*<<< orphan*/ *) ; 

void bfq_add_bfqq_busy(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{
	bfq_log_bfqq(bfqd, bfqq, "add to busy");

	bfq_activate_bfqq(bfqd, bfqq);

	bfq_mark_bfqq_busy(bfqq);
	bfqd->busy_queues[bfqq->ioprio_class - 1]++;

	if (!bfqq->dispatched)
		if (bfqq->wr_coeff == 1)
			bfq_weights_tree_add(bfqd, bfqq,
					     &bfqd->queue_weights_tree);

	if (bfqq->wr_coeff > 1)
		bfqd->wr_busy_queues++;
}