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
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 scalar_t__ arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  eset_insert_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eset_state_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_arena_ind_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_active ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_state_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extent_deactivate_locked(tsdn_t *tsdn, arena_t *arena, eset_t *eset,
    extent_t *extent) {
	assert(extent_arena_ind_get(extent) == arena_ind_get(arena));
	assert(extent_state_get(extent) == extent_state_active);

	extent_state_set(extent, eset_state_get(eset));
	eset_insert_locked(tsdn, eset, extent);
}