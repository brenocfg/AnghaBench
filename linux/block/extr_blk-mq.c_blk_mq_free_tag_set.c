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
struct blk_mq_tag_set {int nr_maps; int /*<<< orphan*/ * tags; TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mq_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_map_and_requests (struct blk_mq_tag_set*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int nr_hw_queues (struct blk_mq_tag_set*) ; 

void blk_mq_free_tag_set(struct blk_mq_tag_set *set)
{
	int i, j;

	for (i = 0; i < nr_hw_queues(set); i++)
		blk_mq_free_map_and_requests(set, i);

	for (j = 0; j < set->nr_maps; j++) {
		kfree(set->map[j].mq_map);
		set->map[j].mq_map = NULL;
	}

	kfree(set->tags);
	set->tags = NULL;
}