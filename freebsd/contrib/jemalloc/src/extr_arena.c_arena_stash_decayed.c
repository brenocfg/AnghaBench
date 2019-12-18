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
typedef  int /*<<< orphan*/  extents_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_list_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t LG_PAGE ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  extent_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extents_evict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
arena_stash_decayed(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extents_t *extents, size_t npages_limit,
	size_t npages_decay_max, extent_list_t *decay_extents) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	/* Stash extents according to npages_limit. */
	size_t nstashed = 0;
	extent_t *extent;
	while (nstashed < npages_decay_max &&
	    (extent = extents_evict(tsdn, arena, r_extent_hooks, extents,
	    npages_limit)) != NULL) {
		extent_list_append(decay_extents, extent);
		nstashed += extent_size_get(extent) >> LG_PAGE;
	}
	return nstashed;
}