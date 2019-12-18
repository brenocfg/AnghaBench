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
struct blk_mq_hw_ctx {TYPE_2__* queue; } ;
struct bfq_data {int /*<<< orphan*/  dispatch; } ;
struct TYPE_4__ {TYPE_1__* elevator; } ;
struct TYPE_3__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 scalar_t__ bfq_tot_busy_queues (struct bfq_data*) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bfq_has_work(struct blk_mq_hw_ctx *hctx)
{
	struct bfq_data *bfqd = hctx->queue->elevator->elevator_data;

	/*
	 * Avoiding lock: a race on bfqd->busy_queues should cause at
	 * most a call to dispatch for nothing
	 */
	return !list_empty_careful(&bfqd->dispatch) ||
		bfq_tot_busy_queues(bfqd) > 0;
}