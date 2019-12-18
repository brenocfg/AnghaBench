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
struct request_queue {int /*<<< orphan*/  nr_requests; struct blk_mq_tag_set* tag_set; } ;
struct blk_mq_tag_set {int /*<<< orphan*/  reserved_tags; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  sched_tags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  blk_mq_alloc_rq_map (struct blk_mq_tag_set*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int blk_mq_alloc_rqs (struct blk_mq_tag_set*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_sched_free_tags (struct blk_mq_tag_set*,struct blk_mq_hw_ctx*,unsigned int) ; 

__attribute__((used)) static int blk_mq_sched_alloc_tags(struct request_queue *q,
				   struct blk_mq_hw_ctx *hctx,
				   unsigned int hctx_idx)
{
	struct blk_mq_tag_set *set = q->tag_set;
	int ret;

	hctx->sched_tags = blk_mq_alloc_rq_map(set, hctx_idx, q->nr_requests,
					       set->reserved_tags);
	if (!hctx->sched_tags)
		return -ENOMEM;

	ret = blk_mq_alloc_rqs(set, hctx->sched_tags, hctx_idx, q->nr_requests);
	if (ret)
		blk_mq_sched_free_tags(set, hctx, hctx_idx);

	return ret;
}