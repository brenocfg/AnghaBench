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
struct cache_lfu_policy_item_ {int dummy; } ;
struct cache_lfu_policy_ {int /*<<< orphan*/ * groups; } ;

/* Variables and functions */
 int CACHELIB_MAX_FREQUENCY ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct cache_lfu_policy_item_* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cache_lfu_policy_item_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_policy_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_policy_*)) ; 
 int /*<<< orphan*/  cache_lfu_policy_destroy_item (struct cache_policy_item_*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct cache_policy_*) ; 

void
destroy_cache_lfu_policy(struct cache_policy_ *policy)
{
	int i;
	struct cache_lfu_policy_ *lfu_policy;
	struct cache_lfu_policy_item_ *lfu_item;

	TRACE_IN(destroy_cache_lfu_policy);
	lfu_policy = (struct cache_lfu_policy_ *)policy;
	for (i = 0; i < CACHELIB_MAX_FREQUENCY; ++i) {
		while (!TAILQ_EMPTY(&(lfu_policy->groups[i]))) {
			lfu_item = TAILQ_FIRST(&(lfu_policy->groups[i]));
			TAILQ_REMOVE(&(lfu_policy->groups[i]), lfu_item,
				entries);
			cache_lfu_policy_destroy_item(
				(struct cache_policy_item_ *)lfu_item);
		}
	}
	free(policy);
	TRACE_OUT(destroy_cache_lfu_policy);
}