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
struct event_base {scalar_t__ running_loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 struct event_base* current_base ; 
 int /*<<< orphan*/  th_base_lock ; 
 int /*<<< orphan*/  update_time_cache (struct event_base*) ; 

int
event_base_update_cache_time(struct event_base *base)
{

	if (!base) {
		base = current_base;
		if (!current_base)
			return -1;
	}

	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	if (base->running_loop)
		update_time_cache(base);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
	return 0;
}