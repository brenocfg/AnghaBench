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
struct cache_queue_policy_item_ {int dummy; } ;
struct cache_queue_policy_ {int dummy; } ;
struct cache_policy_item_ {int dummy; } ;
struct cache_policy_ {int dummy; } ;

/* Variables and functions */
 scalar_t__ TAILQ_PREV (struct cache_queue_policy_item_*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_policy_item_* (*) (struct cache_policy_*,struct cache_policy_item_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_policy_item_* (*) (struct cache_policy_*,struct cache_policy_item_*)) ; 
 int /*<<< orphan*/  cache_queue_policy_head_ ; 
 int /*<<< orphan*/  entries ; 

__attribute__((used)) static struct cache_policy_item_ *
cache_queue_policy_get_prev_item(struct cache_policy_ *policy,
	struct cache_policy_item_ *item)
{
	struct cache_queue_policy_ *queue_policy;
	struct cache_queue_policy_item_	*queue_item;

	TRACE_IN(cache_queue_policy_get_prev_item);
	queue_policy = (struct cache_queue_policy_ *)policy;
	queue_item = (struct cache_queue_policy_item_ *)item;

	TRACE_OUT(cache_queue_policy_get_prev_item);
	return ((struct cache_policy_item_ *)TAILQ_PREV(queue_item,
		cache_queue_policy_head_, entries));
}