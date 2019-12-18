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
struct TYPE_2__ {int /*<<< orphan*/  get_prev_item_func; int /*<<< orphan*/  get_next_item_func; int /*<<< orphan*/  get_last_item_func; int /*<<< orphan*/  get_first_item_func; int /*<<< orphan*/  remove_item_func; int /*<<< orphan*/  add_item_func; int /*<<< orphan*/  destroy_item_func; int /*<<< orphan*/  create_item_func; } ;
struct cache_queue_policy_ {int /*<<< orphan*/  head; TYPE_1__ parent_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_queue_policy_* (*) ()) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_queue_policy_* (*) ()) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_queue_policy_add_item ; 
 int /*<<< orphan*/  cache_queue_policy_create_item ; 
 int /*<<< orphan*/  cache_queue_policy_destroy_item ; 
 int /*<<< orphan*/  cache_queue_policy_get_first_item ; 
 int /*<<< orphan*/  cache_queue_policy_get_last_item ; 
 int /*<<< orphan*/  cache_queue_policy_get_next_item ; 
 int /*<<< orphan*/  cache_queue_policy_get_prev_item ; 
 int /*<<< orphan*/  cache_queue_policy_remove_item ; 
 struct cache_queue_policy_* calloc (int,int) ; 

__attribute__((used)) static struct cache_queue_policy_ *
init_cache_queue_policy(void)
{
	struct cache_queue_policy_	*retval;

	TRACE_IN(init_cache_queue_policy);
	retval = calloc(1,
		sizeof(*retval));
	assert(retval != NULL);

	retval->parent_data.create_item_func = cache_queue_policy_create_item;
	retval->parent_data.destroy_item_func = cache_queue_policy_destroy_item;

	retval->parent_data.add_item_func = cache_queue_policy_add_item;
	retval->parent_data.remove_item_func = cache_queue_policy_remove_item;

	retval->parent_data.get_first_item_func =
		cache_queue_policy_get_first_item;
	retval->parent_data.get_last_item_func =
		cache_queue_policy_get_last_item;
	retval->parent_data.get_next_item_func =
		cache_queue_policy_get_next_item;
	retval->parent_data.get_prev_item_func =
		cache_queue_policy_get_prev_item;

	TAILQ_INIT(&retval->head);
	TRACE_OUT(init_cache_queue_policy);
	return (retval);
}