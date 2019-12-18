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
struct blk_mq_tag_set {int /*<<< orphan*/  numa_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct request_queue* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct request_queue*) ; 
 struct request_queue* blk_alloc_queue_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 struct request_queue* blk_mq_init_allocated_queue (struct blk_mq_tag_set*,struct request_queue*,int) ; 

struct request_queue *blk_mq_init_queue(struct blk_mq_tag_set *set)
{
	struct request_queue *uninit_q, *q;

	uninit_q = blk_alloc_queue_node(GFP_KERNEL, set->numa_node);
	if (!uninit_q)
		return ERR_PTR(-ENOMEM);

	/*
	 * Initialize the queue without an elevator. device_add_disk() will do
	 * the initialization.
	 */
	q = blk_mq_init_allocated_queue(set, uninit_q, false);
	if (IS_ERR(q))
		blk_cleanup_queue(uninit_q);

	return q;
}