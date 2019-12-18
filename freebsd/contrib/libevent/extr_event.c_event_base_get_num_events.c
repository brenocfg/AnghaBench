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
struct event_base {scalar_t__ event_count; scalar_t__ virtual_event_count; scalar_t__ event_count_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 unsigned int EVENT_BASE_COUNT_ACTIVE ; 
 unsigned int EVENT_BASE_COUNT_ADDED ; 
 unsigned int EVENT_BASE_COUNT_VIRTUAL ; 
 int /*<<< orphan*/  th_base_lock ; 

int
event_base_get_num_events(struct event_base *base, unsigned int type)
{
	int r = 0;

	EVBASE_ACQUIRE_LOCK(base, th_base_lock);

	if (type & EVENT_BASE_COUNT_ACTIVE)
		r += base->event_count_active;

	if (type & EVENT_BASE_COUNT_VIRTUAL)
		r += base->virtual_event_count;

	if (type & EVENT_BASE_COUNT_ADDED)
		r += base->event_count;

	EVBASE_RELEASE_LOCK(base, th_base_lock);

	return r;
}