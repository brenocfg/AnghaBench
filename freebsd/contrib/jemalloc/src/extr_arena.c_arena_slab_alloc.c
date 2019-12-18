#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_11__ {int /*<<< orphan*/  bitmap_info; int /*<<< orphan*/  nregs; int /*<<< orphan*/  slab_size; int /*<<< orphan*/  reg_size; } ;
typedef  TYPE_1__ bin_info_t ;
struct TYPE_12__ {int /*<<< orphan*/  extents_muzzy; int /*<<< orphan*/  extents_dirty; } ;
typedef  TYPE_2__ arena_t ;
struct TYPE_13__ {int /*<<< orphan*/  bitmap; } ;
typedef  TYPE_3__ arena_slab_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * EXTENT_HOOKS_INITIALIZER ; 
 int LG_PAGE ; 
 int /*<<< orphan*/  PAGE ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_nactive_add (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * arena_slab_alloc_hard (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extent_nfree_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int extent_size_get (int /*<<< orphan*/ *) ; 
 TYPE_3__* extent_slab_data_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_slab_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extents_alloc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  sz_size2index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static extent_t *
arena_slab_alloc(tsdn_t *tsdn, arena_t *arena, szind_t binind,
    const bin_info_t *bin_info) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extent_hooks_t *extent_hooks = EXTENT_HOOKS_INITIALIZER;
	szind_t szind = sz_size2index(bin_info->reg_size);
	bool zero = false;
	bool commit = true;
	extent_t *slab = extents_alloc(tsdn, arena, &extent_hooks,
	    &arena->extents_dirty, NULL, bin_info->slab_size, 0, PAGE, true,
	    binind, &zero, &commit);
	if (slab == NULL) {
		slab = extents_alloc(tsdn, arena, &extent_hooks,
		    &arena->extents_muzzy, NULL, bin_info->slab_size, 0, PAGE,
		    true, binind, &zero, &commit);
	}
	if (slab == NULL) {
		slab = arena_slab_alloc_hard(tsdn, arena, &extent_hooks,
		    bin_info, szind);
		if (slab == NULL) {
			return NULL;
		}
	}
	assert(extent_slab_get(slab));

	/* Initialize slab internals. */
	arena_slab_data_t *slab_data = extent_slab_data_get(slab);
	extent_nfree_set(slab, bin_info->nregs);
	bitmap_init(slab_data->bitmap, &bin_info->bitmap_info, false);

	arena_nactive_add(arena, extent_size_get(slab) >> LG_PAGE);

	return slab;
}