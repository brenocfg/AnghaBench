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
struct bfq_data {int /*<<< orphan*/  wr_busy_queues; int /*<<< orphan*/ * busy_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_clear_bfqq_busy (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_deactivate_bfqq (struct bfq_data*,struct bfq_queue*,int,int) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*) ; 
 int /*<<< orphan*/  bfq_weights_tree_remove (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfqg_stats_update_dequeue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfqq_group (struct bfq_queue*) ; 

void bfq_del_bfqq_busy(struct bfq_data *bfqd, struct bfq_queue *bfqq,
		       bool expiration)
{
	bfq_log_bfqq(bfqd, bfqq, "del from busy");

	bfq_clear_bfqq_busy(bfqq);

	bfqd->busy_queues[bfqq->ioprio_class - 1]--;

	if (bfqq->wr_coeff > 1)
		bfqd->wr_busy_queues--;

	bfqg_stats_update_dequeue(bfqq_group(bfqq));

	bfq_deactivate_bfqq(bfqd, bfqq, true, expiration);

	if (!bfqq->dispatched)
		bfq_weights_tree_remove(bfqd, bfqq);
}