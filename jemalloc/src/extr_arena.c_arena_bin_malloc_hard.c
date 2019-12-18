#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_10__ {int /*<<< orphan*/ * slabcur; } ;
typedef  TYPE_1__ bin_t ;
struct TYPE_11__ {scalar_t__ nregs; } ;
typedef  TYPE_2__ bin_info_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_bin_lower_slab (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * arena_bin_nonfull_slab_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,size_t,unsigned int) ; 
 int /*<<< orphan*/  arena_bin_slabs_full_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_dalloc_bin_slab (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  arena_is_auto (int /*<<< orphan*/ *) ; 
 void* arena_slab_reg_alloc (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* bin_infos ; 
 scalar_t__ extent_nfree_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
arena_bin_malloc_hard(tsdn_t *tsdn, arena_t *arena, bin_t *bin,
    szind_t binind, unsigned binshard) {
	const bin_info_t *bin_info;
	extent_t *slab;

	bin_info = &bin_infos[binind];
	if (!arena_is_auto(arena) && bin->slabcur != NULL) {
		arena_bin_slabs_full_insert(arena, bin, bin->slabcur);
		bin->slabcur = NULL;
	}
	slab = arena_bin_nonfull_slab_get(tsdn, arena, bin, binind, binshard);
	if (bin->slabcur != NULL) {
		/*
		 * Another thread updated slabcur while this one ran without the
		 * bin lock in arena_bin_nonfull_slab_get().
		 */
		if (extent_nfree_get(bin->slabcur) > 0) {
			void *ret = arena_slab_reg_alloc(bin->slabcur,
			    bin_info);
			if (slab != NULL) {
				/*
				 * arena_slab_alloc() may have allocated slab,
				 * or it may have been pulled from
				 * slabs_nonfull.  Therefore it is unsafe to
				 * make any assumptions about how slab has
				 * previously been used, and
				 * arena_bin_lower_slab() must be called, as if
				 * a region were just deallocated from the slab.
				 */
				if (extent_nfree_get(slab) == bin_info->nregs) {
					arena_dalloc_bin_slab(tsdn, arena, slab,
					    bin);
				} else {
					arena_bin_lower_slab(tsdn, arena, slab,
					    bin);
				}
			}
			return ret;
		}

		arena_bin_slabs_full_insert(arena, bin, bin->slabcur);
		bin->slabcur = NULL;
	}

	if (slab == NULL) {
		return NULL;
	}
	bin->slabcur = slab;

	assert(extent_nfree_get(bin->slabcur) > 0);

	return arena_slab_reg_alloc(slab, bin_info);
}