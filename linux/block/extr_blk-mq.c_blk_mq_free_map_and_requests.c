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
struct blk_mq_tag_set {int /*<<< orphan*/ ** tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_rq_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_rqs (struct blk_mq_tag_set*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void blk_mq_free_map_and_requests(struct blk_mq_tag_set *set,
					 unsigned int hctx_idx)
{
	if (set->tags && set->tags[hctx_idx]) {
		blk_mq_free_rqs(set, set->tags[hctx_idx], hctx_idx);
		blk_mq_free_rq_map(set->tags[hctx_idx]);
		set->tags[hctx_idx] = NULL;
	}
}