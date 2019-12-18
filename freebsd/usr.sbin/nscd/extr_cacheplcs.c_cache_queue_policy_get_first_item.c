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
struct cache_queue_policy_ {int /*<<< orphan*/  head; } ;
struct cache_policy_item_ {int dummy; } ;
struct cache_policy_ {int dummy; } ;

/* Variables and functions */
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_policy_item_* (*) (struct cache_policy_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_policy_item_* (*) (struct cache_policy_*)) ; 

__attribute__((used)) static struct cache_policy_item_ *
cache_queue_policy_get_first_item(struct cache_policy_ *policy)
{
	struct cache_queue_policy_ *queue_policy;

	TRACE_IN(cache_queue_policy_get_first_item);
	queue_policy = (struct cache_queue_policy_ *)policy;
	TRACE_OUT(cache_queue_policy_get_first_item);
	return ((struct cache_policy_item_ *)TAILQ_FIRST(&queue_policy->head));
}