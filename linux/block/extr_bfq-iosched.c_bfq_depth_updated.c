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
struct blk_mq_tags {int /*<<< orphan*/  bitmap_tags; } ;
struct blk_mq_hw_ctx {struct blk_mq_tags* sched_tags; TYPE_2__* queue; } ;
struct bfq_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* elevator; } ;
struct TYPE_3__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 unsigned int bfq_update_depths (struct bfq_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbitmap_queue_min_shallow_depth (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void bfq_depth_updated(struct blk_mq_hw_ctx *hctx)
{
	struct bfq_data *bfqd = hctx->queue->elevator->elevator_data;
	struct blk_mq_tags *tags = hctx->sched_tags;
	unsigned int min_shallow;

	min_shallow = bfq_update_depths(bfqd, &tags->bitmap_tags);
	sbitmap_queue_min_shallow_depth(&tags->bitmap_tags, min_shallow);
}