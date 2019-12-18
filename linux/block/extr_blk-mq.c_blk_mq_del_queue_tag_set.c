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
struct request_queue {int /*<<< orphan*/  tag_set_list; struct blk_mq_tag_set* tag_set; } ;
struct blk_mq_tag_set {int /*<<< orphan*/  tag_list_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  tag_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_TAG_SHARED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_update_tag_set_depth (struct blk_mq_tag_set*,int) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blk_mq_del_queue_tag_set(struct request_queue *q)
{
	struct blk_mq_tag_set *set = q->tag_set;

	mutex_lock(&set->tag_list_lock);
	list_del_rcu(&q->tag_set_list);
	if (list_is_singular(&set->tag_list)) {
		/* just transitioned to unshared */
		set->flags &= ~BLK_MQ_F_TAG_SHARED;
		/* update existing queue */
		blk_mq_update_tag_set_depth(set, false);
	}
	mutex_unlock(&set->tag_list_lock);
	INIT_LIST_HEAD(&q->tag_set_list);
}