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
struct event_debug_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOCK_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct event_debug_entry** HT_NEXT_RMV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct event_debug_entry**) ; 
 struct event_debug_entry** HT_START (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_debug_map ; 
 int /*<<< orphan*/  event_debug_map_lock_ ; 
 scalar_t__ event_debug_mode_on_ ; 
 int /*<<< orphan*/  global_debug_map ; 
 int /*<<< orphan*/  mm_free (struct event_debug_entry*) ; 

void
event_disable_debug_mode(void)
{
#ifndef EVENT__DISABLE_DEBUG_MODE
	struct event_debug_entry **ent, *victim;

	EVLOCK_LOCK(event_debug_map_lock_, 0);
	for (ent = HT_START(event_debug_map, &global_debug_map); ent; ) {
		victim = *ent;
		ent = HT_NEXT_RMV(event_debug_map, &global_debug_map, ent);
		mm_free(victim);
	}
	HT_CLEAR(event_debug_map, &global_debug_map);
	EVLOCK_UNLOCK(event_debug_map_lock_ , 0);

	event_debug_mode_on_  = 0;
#endif
}