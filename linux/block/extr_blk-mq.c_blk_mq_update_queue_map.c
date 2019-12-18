#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct blk_mq_tag_set {int nr_maps; int /*<<< orphan*/ * map; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* map_queues ) (struct blk_mq_tag_set*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t HCTX_TYPE_DEFAULT ; 
 int /*<<< orphan*/  blk_mq_clear_mq_map (int /*<<< orphan*/ *) ; 
 int blk_mq_map_queues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_kdump_kernel () ; 
 int stub1 (struct blk_mq_tag_set*) ; 

__attribute__((used)) static int blk_mq_update_queue_map(struct blk_mq_tag_set *set)
{
	if (set->ops->map_queues && !is_kdump_kernel()) {
		int i;

		/*
		 * transport .map_queues is usually done in the following
		 * way:
		 *
		 * for (queue = 0; queue < set->nr_hw_queues; queue++) {
		 * 	mask = get_cpu_mask(queue)
		 * 	for_each_cpu(cpu, mask)
		 * 		set->map[x].mq_map[cpu] = queue;
		 * }
		 *
		 * When we need to remap, the table has to be cleared for
		 * killing stale mapping since one CPU may not be mapped
		 * to any hw queue.
		 */
		for (i = 0; i < set->nr_maps; i++)
			blk_mq_clear_mq_map(&set->map[i]);

		return set->ops->map_queues(set);
	} else {
		BUG_ON(set->nr_maps > 1);
		return blk_mq_map_queues(&set->map[HCTX_TYPE_DEFAULT]);
	}
}