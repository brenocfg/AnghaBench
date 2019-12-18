#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {scalar_t__ nregs; int /*<<< orphan*/  bitmap_info; } ;
typedef  TYPE_1__ bin_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  bitmap; } ;
typedef  TYPE_2__ arena_slab_data_t ;

/* Variables and functions */
 size_t arena_slab_regind (int /*<<< orphan*/ *,size_t,void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* bin_infos ; 
 int bitmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bitmap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ extent_nfree_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_nfree_inc (int /*<<< orphan*/ *) ; 
 size_t extent_szind_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_slab_reg_dalloc(extent_t *slab, arena_slab_data_t *slab_data, void *ptr) {
	szind_t binind = extent_szind_get(slab);
	const bin_info_t *bin_info = &bin_infos[binind];
	size_t regind = arena_slab_regind(slab, binind, ptr);

	assert(extent_nfree_get(slab) < bin_info->nregs);
	/* Freeing an unallocated pointer can cause assertion failure. */
	assert(bitmap_get(slab_data->bitmap, &bin_info->bitmap_info, regind));

	bitmap_unset(slab_data->bitmap, &bin_info->bitmap_info, regind);
	extent_nfree_inc(slab);
}