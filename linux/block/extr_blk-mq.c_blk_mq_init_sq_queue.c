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
struct request_queue {int dummy; } ;
struct blk_mq_tag_set {int nr_hw_queues; int nr_maps; unsigned int queue_depth; unsigned int flags; int /*<<< orphan*/  numa_node; struct blk_mq_ops const* ops; } ;
struct blk_mq_ops {int dummy; } ;

/* Variables and functions */
 struct request_queue* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int blk_mq_alloc_tag_set (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (struct blk_mq_tag_set*) ; 
 struct request_queue* blk_mq_init_queue (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  memset (struct blk_mq_tag_set*,int /*<<< orphan*/ ,int) ; 

struct request_queue *blk_mq_init_sq_queue(struct blk_mq_tag_set *set,
					   const struct blk_mq_ops *ops,
					   unsigned int queue_depth,
					   unsigned int set_flags)
{
	struct request_queue *q;
	int ret;

	memset(set, 0, sizeof(*set));
	set->ops = ops;
	set->nr_hw_queues = 1;
	set->nr_maps = 1;
	set->queue_depth = queue_depth;
	set->numa_node = NUMA_NO_NODE;
	set->flags = set_flags;

	ret = blk_mq_alloc_tag_set(set);
	if (ret)
		return ERR_PTR(ret);

	q = blk_mq_init_queue(set);
	if (IS_ERR(q)) {
		blk_mq_free_tag_set(set);
		return q;
	}

	return q;
}