#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_7__ {int /*<<< orphan*/ * slabcur; } ;
typedef  TYPE_1__ bin_t ;
struct TYPE_8__ {int nregs; } ;
typedef  TYPE_2__ bin_info_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_bin_slabs_full_remove (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_bin_slabs_nonfull_remove (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* bin_infos ; 
 size_t extent_szind_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_dissociate_bin_slab(arena_t *arena, extent_t *slab, bin_t *bin) {
	/* Dissociate slab from bin. */
	if (slab == bin->slabcur) {
		bin->slabcur = NULL;
	} else {
		szind_t binind = extent_szind_get(slab);
		const bin_info_t *bin_info = &bin_infos[binind];

		/*
		 * The following block's conditional is necessary because if the
		 * slab only contains one region, then it never gets inserted
		 * into the non-full slabs heap.
		 */
		if (bin_info->nregs == 1) {
			arena_bin_slabs_full_remove(arena, bin, slab);
		} else {
			arena_bin_slabs_nonfull_remove(bin, slab);
		}
	}
}