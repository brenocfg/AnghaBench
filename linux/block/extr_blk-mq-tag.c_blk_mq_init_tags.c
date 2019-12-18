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
struct blk_mq_tags {unsigned int nr_tags; unsigned int nr_reserved_tags; } ;

/* Variables and functions */
 unsigned int BLK_MQ_TAG_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct blk_mq_tags* blk_mq_init_bitmap_tags (struct blk_mq_tags*,int,int) ; 
 struct blk_mq_tags* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct blk_mq_tags *blk_mq_init_tags(unsigned int total_tags,
				     unsigned int reserved_tags,
				     int node, int alloc_policy)
{
	struct blk_mq_tags *tags;

	if (total_tags > BLK_MQ_TAG_MAX) {
		pr_err("blk-mq: tag depth too large\n");
		return NULL;
	}

	tags = kzalloc_node(sizeof(*tags), GFP_KERNEL, node);
	if (!tags)
		return NULL;

	tags->nr_tags = total_tags;
	tags->nr_reserved_tags = reserved_tags;

	return blk_mq_init_bitmap_tags(tags, node, alloc_policy);
}