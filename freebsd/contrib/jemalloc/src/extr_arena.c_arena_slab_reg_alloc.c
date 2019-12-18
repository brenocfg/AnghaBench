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
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {size_t reg_size; int /*<<< orphan*/  bitmap_info; } ;
typedef  TYPE_1__ bin_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  bitmap; } ;
typedef  TYPE_2__ arena_slab_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bitmap_full (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t bitmap_sfu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ extent_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_nfree_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_nfree_get (int /*<<< orphan*/ *) ; 
 TYPE_2__* extent_slab_data_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
arena_slab_reg_alloc(extent_t *slab, const bin_info_t *bin_info) {
	void *ret;
	arena_slab_data_t *slab_data = extent_slab_data_get(slab);
	size_t regind;

	assert(extent_nfree_get(slab) > 0);
	assert(!bitmap_full(slab_data->bitmap, &bin_info->bitmap_info));

	regind = bitmap_sfu(slab_data->bitmap, &bin_info->bitmap_info);
	ret = (void *)((uintptr_t)extent_addr_get(slab) +
	    (uintptr_t)(bin_info->reg_size * regind));
	extent_nfree_dec(slab);
	return ret;
}