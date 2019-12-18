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
struct cache_lfu_policy_item_ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (struct cache_policy_item_* (*) ()) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_policy_item_* (*) ()) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct cache_lfu_policy_item_* calloc (int,int) ; 

__attribute__((used)) static struct cache_policy_item_ *
cache_lfu_policy_create_item(void)
{
	struct cache_lfu_policy_item_ *retval;

	TRACE_IN(cache_lfu_policy_create_item);
	retval = calloc(1,
		sizeof(*retval));
	assert(retval != NULL);

	TRACE_OUT(cache_lfu_policy_create_item);
	return ((struct cache_policy_item_ *)retval);
}