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
struct cache_queue_policy_ {int dummy; } ;
struct cache_policy_ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_policy_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_policy_*)) ; 
 int /*<<< orphan*/  destroy_cache_queue_policy (struct cache_queue_policy_*) ; 

void
destroy_cache_fifo_policy(struct cache_policy_ *policy)
{
	struct cache_queue_policy_	*queue_policy;

	TRACE_IN(destroy_cache_fifo_policy);
	queue_policy = (struct cache_queue_policy_ *)policy;
	destroy_cache_queue_policy(queue_policy);
	TRACE_OUT(destroy_cache_fifo_policy);
}