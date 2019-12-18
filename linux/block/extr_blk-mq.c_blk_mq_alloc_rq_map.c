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
struct request {int dummy; } ;
struct blk_mq_tags {void* rqs; void* static_rqs; } ;
struct blk_mq_tag_set {int numa_node; int /*<<< orphan*/  flags; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_FLAG_TO_ALLOC_POLICY (int /*<<< orphan*/ ) ; 
 int GFP_NOIO ; 
 size_t HCTX_TYPE_DEFAULT ; 
 int NUMA_NO_NODE ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  blk_mq_free_tags (struct blk_mq_tags*) ; 
 int blk_mq_hw_queue_to_node (int /*<<< orphan*/ *,unsigned int) ; 
 struct blk_mq_tags* blk_mq_init_tags (unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 void* kcalloc_node (unsigned int,int,int,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 

struct blk_mq_tags *blk_mq_alloc_rq_map(struct blk_mq_tag_set *set,
					unsigned int hctx_idx,
					unsigned int nr_tags,
					unsigned int reserved_tags)
{
	struct blk_mq_tags *tags;
	int node;

	node = blk_mq_hw_queue_to_node(&set->map[HCTX_TYPE_DEFAULT], hctx_idx);
	if (node == NUMA_NO_NODE)
		node = set->numa_node;

	tags = blk_mq_init_tags(nr_tags, reserved_tags, node,
				BLK_MQ_FLAG_TO_ALLOC_POLICY(set->flags));
	if (!tags)
		return NULL;

	tags->rqs = kcalloc_node(nr_tags, sizeof(struct request *),
				 GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY,
				 node);
	if (!tags->rqs) {
		blk_mq_free_tags(tags);
		return NULL;
	}

	tags->static_rqs = kcalloc_node(nr_tags, sizeof(struct request *),
					GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY,
					node);
	if (!tags->static_rqs) {
		kfree(tags->rqs);
		blk_mq_free_tags(tags);
		return NULL;
	}

	return tags;
}