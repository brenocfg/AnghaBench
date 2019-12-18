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
struct cache_policy_ {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  get_prev_item_func; int /*<<< orphan*/  get_next_item_func; int /*<<< orphan*/  get_last_item_func; int /*<<< orphan*/  get_first_item_func; int /*<<< orphan*/  remove_item_func; int /*<<< orphan*/  update_item_func; int /*<<< orphan*/  add_item_func; int /*<<< orphan*/  destroy_item_func; int /*<<< orphan*/  create_item_func; } ;
struct cache_lfu_policy_ {int /*<<< orphan*/ * groups; TYPE_1__ parent_data; } ;

/* Variables and functions */
 int CACHELIB_MAX_FREQUENCY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_policy_* (*) ()) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_policy_* (*) ()) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_lfu_policy_add_item ; 
 int /*<<< orphan*/  cache_lfu_policy_create_item ; 
 int /*<<< orphan*/  cache_lfu_policy_destroy_item ; 
 int /*<<< orphan*/  cache_lfu_policy_get_first_item ; 
 int /*<<< orphan*/  cache_lfu_policy_get_last_item ; 
 int /*<<< orphan*/  cache_lfu_policy_get_next_item ; 
 int /*<<< orphan*/  cache_lfu_policy_get_prev_item ; 
 int /*<<< orphan*/  cache_lfu_policy_remove_item ; 
 int /*<<< orphan*/  cache_lfu_policy_update_item ; 
 struct cache_lfu_policy_* calloc (int,int) ; 

struct cache_policy_ *
init_cache_lfu_policy(void)
{
	int i;
	struct cache_lfu_policy_ *retval;

	TRACE_IN(init_cache_lfu_policy);
	retval = calloc(1,
		sizeof(*retval));
	assert(retval != NULL);

	retval->parent_data.create_item_func = cache_lfu_policy_create_item;
	retval->parent_data.destroy_item_func = cache_lfu_policy_destroy_item;

	retval->parent_data.add_item_func = cache_lfu_policy_add_item;
	retval->parent_data.update_item_func = cache_lfu_policy_update_item;
	retval->parent_data.remove_item_func = cache_lfu_policy_remove_item;

	retval->parent_data.get_first_item_func =
		cache_lfu_policy_get_first_item;
	retval->parent_data.get_last_item_func =
		cache_lfu_policy_get_last_item;
	retval->parent_data.get_next_item_func =
		cache_lfu_policy_get_next_item;
	retval->parent_data.get_prev_item_func =
		cache_lfu_policy_get_prev_item;

	for (i = 0; i < CACHELIB_MAX_FREQUENCY; ++i)
		TAILQ_INIT(&(retval->groups[i]));

	TRACE_OUT(init_cache_lfu_policy);
	return ((struct cache_policy_ *)retval);
}