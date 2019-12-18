#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_6__ {int /*<<< orphan*/  reslabs; } ;
struct TYPE_7__ {TYPE_1__ stats; int /*<<< orphan*/ * slabcur; } ;
typedef  TYPE_2__ bin_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_bin_slabs_full_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_bin_slabs_nonfull_insert (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_stats ; 
 scalar_t__ extent_nfree_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_snad_comp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_bin_lower_slab(tsdn_t *tsdn, arena_t *arena, extent_t *slab,
    bin_t *bin) {
	assert(extent_nfree_get(slab) > 0);

	/*
	 * Make sure that if bin->slabcur is non-NULL, it refers to the
	 * oldest/lowest non-full slab.  It is okay to NULL slabcur out rather
	 * than proactively keeping it pointing at the oldest/lowest non-full
	 * slab.
	 */
	if (bin->slabcur != NULL && extent_snad_comp(bin->slabcur, slab) > 0) {
		/* Switch slabcur. */
		if (extent_nfree_get(bin->slabcur) > 0) {
			arena_bin_slabs_nonfull_insert(bin, bin->slabcur);
		} else {
			arena_bin_slabs_full_insert(arena, bin, bin->slabcur);
		}
		bin->slabcur = slab;
		if (config_stats) {
			bin->stats.reslabs++;
		}
	} else {
		arena_bin_slabs_nonfull_insert(bin, slab);
	}
}