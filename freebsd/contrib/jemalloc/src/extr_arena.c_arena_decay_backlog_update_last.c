#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t nunpurged; size_t* backlog; size_t ceil_npages; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 int SMOOTHSTEP_NSTEPS ; 
 size_t arena_decay_backlog_npages_limit (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_debug ; 

__attribute__((used)) static void
arena_decay_backlog_update_last(arena_decay_t *decay, size_t current_npages) {
	size_t npages_delta = (current_npages > decay->nunpurged) ?
	    current_npages - decay->nunpurged : 0;
	decay->backlog[SMOOTHSTEP_NSTEPS-1] = npages_delta;

	if (config_debug) {
		if (current_npages > decay->ceil_npages) {
			decay->ceil_npages = current_npages;
		}
		size_t npages_limit = arena_decay_backlog_npages_limit(decay);
		assert(decay->ceil_npages >= npages_limit);
		if (decay->ceil_npages > npages_limit) {
			decay->ceil_npages = npages_limit;
		}
	}
}