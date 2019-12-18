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
struct cache_policy_item_ {int dummy; } ;
struct cache_policy_ {int dummy; } ;
struct cache_lfu_policy_item_ {int frequency; } ;
struct cache_lfu_policy_ {int /*<<< orphan*/ * groups; } ;

/* Variables and functions */
 int CACHELIB_MAX_FREQUENCY ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct cache_lfu_policy_item_* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct cache_lfu_policy_item_* TAILQ_NEXT (struct cache_lfu_policy_item_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_policy_item_* (*) (struct cache_policy_*,struct cache_policy_item_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_policy_item_* (*) (struct cache_policy_*,struct cache_policy_item_*)) ; 
 int /*<<< orphan*/  entries ; 

__attribute__((used)) static struct cache_policy_item_ *
cache_lfu_policy_get_next_item(struct cache_policy_ *policy,
	struct cache_policy_item_ *item)
{
	struct cache_lfu_policy_ *lfu_policy;
	struct cache_lfu_policy_item_ *lfu_item;
	int i;

	TRACE_IN(cache_lfu_policy_get_next_item);
	lfu_policy = (struct cache_lfu_policy_ *)policy;
	lfu_item = TAILQ_NEXT((struct cache_lfu_policy_item_ *)item, entries);
	if (lfu_item == NULL)
	{
		for (i = ((struct cache_lfu_policy_item_ *)item)->frequency + 1;
			i < CACHELIB_MAX_FREQUENCY; ++i) {
			if (!TAILQ_EMPTY(&(lfu_policy->groups[i]))) {
			    lfu_item = TAILQ_FIRST(&(lfu_policy->groups[i]));
			    break;
			}
		}
	}

	TRACE_OUT(cache_lfu_policy_get_next_item);
	return ((struct cache_policy_item_ *)lfu_item);
}