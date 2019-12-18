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
struct event_debug_entry {struct event const* ptr; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOCK_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct event_debug_entry* HT_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct event_debug_entry*) ; 
 int /*<<< orphan*/  event_debug_map ; 
 int /*<<< orphan*/  event_debug_map_lock_ ; 
 int /*<<< orphan*/  event_debug_mode_on_ ; 
 int event_debug_mode_too_late ; 
 int /*<<< orphan*/  global_debug_map ; 
 int /*<<< orphan*/  mm_free (struct event_debug_entry*) ; 

__attribute__((used)) static void event_debug_note_teardown_(const struct event *ev)
{
	struct event_debug_entry *dent, find;

	if (!event_debug_mode_on_)
		goto out;

	find.ptr = ev;
	EVLOCK_LOCK(event_debug_map_lock_, 0);
	dent = HT_REMOVE(event_debug_map, &global_debug_map, &find);
	if (dent)
		mm_free(dent);
	EVLOCK_UNLOCK(event_debug_map_lock_, 0);

out:
	event_debug_mode_too_late = 1;
}