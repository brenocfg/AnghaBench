#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_5__ {int /*<<< orphan*/  eset_muzzy; int /*<<< orphan*/  decay_muzzy; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int arena_decay_impl (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ arena_muzzy_decay_ms_get (TYPE_1__*) ; 
 scalar_t__ eset_npages_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
arena_decay_muzzy(tsdn_t *tsdn, arena_t *arena, bool is_background_thread,
    bool all) {
	if (eset_npages_get(&arena->eset_muzzy) == 0 &&
	    arena_muzzy_decay_ms_get(arena) <= 0) {
		return false;
	}
	return arena_decay_impl(tsdn, arena, &arena->decay_muzzy,
	    &arena->eset_muzzy, is_background_thread, all);
}