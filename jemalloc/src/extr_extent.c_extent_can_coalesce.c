#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 scalar_t__ arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ extent_arena_ind_get (int /*<<< orphan*/  const*) ; 
 scalar_t__ extent_committed_get (int /*<<< orphan*/  const*) ; 
 scalar_t__ extent_state_active ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool
extent_can_coalesce(arena_t *arena, eset_t *eset, const extent_t *inner,
    const extent_t *outer) {
	assert(extent_arena_ind_get(inner) == arena_ind_get(arena));
	if (extent_arena_ind_get(outer) != arena_ind_get(arena)) {
		return false;
	}

	assert(extent_state_get(inner) == extent_state_active);
	if (extent_state_get(outer) != eset->state) {
		return false;
	}

	if (extent_committed_get(inner) != extent_committed_get(outer)) {
		return false;
	}

	return true;
}