#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_5__ {unsigned int arena_ind; } ;
typedef  TYPE_1__ ctl_arena_t ;
struct TYPE_6__ {unsigned int narenas; int /*<<< orphan*/  destroyed; } ;

/* Variables and functions */
 int UINT_MAX ; 
 int /*<<< orphan*/ * arena_init (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arenas_i_impl (int /*<<< orphan*/ *,unsigned int,int,int) ; 
 TYPE_4__* ctl_arenas ; 
 int /*<<< orphan*/  destroyed_link ; 
 TYPE_1__* ql_last (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_remove (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned
ctl_arena_init(tsd_t *tsd, extent_hooks_t *extent_hooks) {
	unsigned arena_ind;
	ctl_arena_t *ctl_arena;

	if ((ctl_arena = ql_last(&ctl_arenas->destroyed, destroyed_link)) !=
	    NULL) {
		ql_remove(&ctl_arenas->destroyed, ctl_arena, destroyed_link);
		arena_ind = ctl_arena->arena_ind;
	} else {
		arena_ind = ctl_arenas->narenas;
	}

	/* Trigger stats allocation. */
	if (arenas_i_impl(tsd, arena_ind, false, true) == NULL) {
		return UINT_MAX;
	}

	/* Initialize new arena. */
	if (arena_init(tsd_tsdn(tsd), arena_ind, extent_hooks) == NULL) {
		return UINT_MAX;
	}

	if (arena_ind == ctl_arenas->narenas) {
		ctl_arenas->narenas++;
	}

	return arena_ind;
}