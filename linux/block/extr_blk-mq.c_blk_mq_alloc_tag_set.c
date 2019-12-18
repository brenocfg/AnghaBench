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
struct blk_mq_tags {int dummy; } ;
struct blk_mq_tag_set {int nr_hw_queues; int queue_depth; int reserved_tags; int nr_maps; int /*<<< orphan*/ * tags; TYPE_2__* map; int /*<<< orphan*/  tag_list; int /*<<< orphan*/  tag_list_lock; int /*<<< orphan*/  numa_node; TYPE_1__* ops; } ;
struct TYPE_4__ {int nr_queues; int /*<<< orphan*/ * mq_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  put_budget; int /*<<< orphan*/  get_budget; int /*<<< orphan*/  queue_rq; } ;

/* Variables and functions */
 int BLK_MQ_MAX_DEPTH ; 
 int BLK_MQ_TAG_MIN ; 
 int BLK_MQ_UNIQUE_TAG_BITS ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HCTX_MAX_TYPES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int blk_mq_alloc_rq_maps (struct blk_mq_tag_set*) ; 
 int blk_mq_update_queue_map (struct blk_mq_tag_set*) ; 
 scalar_t__ is_kdump_kernel () ; 
 void* kcalloc_node (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int min (unsigned int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 
 int nr_hw_queues (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

int blk_mq_alloc_tag_set(struct blk_mq_tag_set *set)
{
	int i, ret;

	BUILD_BUG_ON(BLK_MQ_MAX_DEPTH > 1 << BLK_MQ_UNIQUE_TAG_BITS);

	if (!set->nr_hw_queues)
		return -EINVAL;
	if (!set->queue_depth)
		return -EINVAL;
	if (set->queue_depth < set->reserved_tags + BLK_MQ_TAG_MIN)
		return -EINVAL;

	if (!set->ops->queue_rq)
		return -EINVAL;

	if (!set->ops->get_budget ^ !set->ops->put_budget)
		return -EINVAL;

	if (set->queue_depth > BLK_MQ_MAX_DEPTH) {
		pr_info("blk-mq: reduced tag depth to %u\n",
			BLK_MQ_MAX_DEPTH);
		set->queue_depth = BLK_MQ_MAX_DEPTH;
	}

	if (!set->nr_maps)
		set->nr_maps = 1;
	else if (set->nr_maps > HCTX_MAX_TYPES)
		return -EINVAL;

	/*
	 * If a crashdump is active, then we are potentially in a very
	 * memory constrained environment. Limit us to 1 queue and
	 * 64 tags to prevent using too much memory.
	 */
	if (is_kdump_kernel()) {
		set->nr_hw_queues = 1;
		set->nr_maps = 1;
		set->queue_depth = min(64U, set->queue_depth);
	}
	/*
	 * There is no use for more h/w queues than cpus if we just have
	 * a single map
	 */
	if (set->nr_maps == 1 && set->nr_hw_queues > nr_cpu_ids)
		set->nr_hw_queues = nr_cpu_ids;

	set->tags = kcalloc_node(nr_hw_queues(set), sizeof(struct blk_mq_tags *),
				 GFP_KERNEL, set->numa_node);
	if (!set->tags)
		return -ENOMEM;

	ret = -ENOMEM;
	for (i = 0; i < set->nr_maps; i++) {
		set->map[i].mq_map = kcalloc_node(nr_cpu_ids,
						  sizeof(set->map[i].mq_map[0]),
						  GFP_KERNEL, set->numa_node);
		if (!set->map[i].mq_map)
			goto out_free_mq_map;
		set->map[i].nr_queues = is_kdump_kernel() ? 1 : set->nr_hw_queues;
	}

	ret = blk_mq_update_queue_map(set);
	if (ret)
		goto out_free_mq_map;

	ret = blk_mq_alloc_rq_maps(set);
	if (ret)
		goto out_free_mq_map;

	mutex_init(&set->tag_list_lock);
	INIT_LIST_HEAD(&set->tag_list);

	return 0;

out_free_mq_map:
	for (i = 0; i < set->nr_maps; i++) {
		kfree(set->map[i].mq_map);
		set->map[i].mq_map = NULL;
	}
	kfree(set->tags);
	set->tags = NULL;
	return ret;
}