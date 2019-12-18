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
struct TYPE_2__ {int /*<<< orphan*/  update_item_func; } ;
struct cache_queue_policy_ {TYPE_1__ parent_data; } ;
struct cache_policy_ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (struct cache_policy_* (*) ()) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_policy_* (*) ()) ; 
 int /*<<< orphan*/  cache_lru_policy_update_item ; 
 struct cache_queue_policy_* init_cache_queue_policy () ; 

struct cache_policy_ *
init_cache_lru_policy(void)
{
	struct cache_queue_policy_ *retval;

	TRACE_IN(init_cache_lru_policy);
	retval = init_cache_queue_policy();
	retval->parent_data.update_item_func = cache_lru_policy_update_item;

	TRACE_OUT(init_cache_lru_policy);
	return ((struct cache_policy_ *)retval);
}