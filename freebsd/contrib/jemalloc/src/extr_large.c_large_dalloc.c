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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_decay_tick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  large_dalloc_finish_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  large_dalloc_prep_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
large_dalloc(tsdn_t *tsdn, extent_t *extent) {
	arena_t *arena = extent_arena_get(extent);
	large_dalloc_prep_impl(tsdn, arena, extent, false);
	large_dalloc_finish_impl(tsdn, arena, extent);
	arena_decay_tick(tsdn, arena);
}