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
struct blk_mq_tag_set {int nr_hw_queues; int /*<<< orphan*/ * tags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __blk_mq_alloc_rq_map (struct blk_mq_tag_set*,int) ; 
 int /*<<< orphan*/  blk_mq_free_rq_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __blk_mq_alloc_rq_maps(struct blk_mq_tag_set *set)
{
	int i;

	for (i = 0; i < set->nr_hw_queues; i++)
		if (!__blk_mq_alloc_rq_map(set, i))
			goto out_unwind;

	return 0;

out_unwind:
	while (--i >= 0)
		blk_mq_free_rq_map(set->tags[i]);

	return -ENOMEM;
}