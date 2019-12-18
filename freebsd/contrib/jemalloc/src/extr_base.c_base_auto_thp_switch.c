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
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_7__ {int auto_thp_switched; scalar_t__ n_thp; TYPE_2__* blocks; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ base_t ;
struct TYPE_8__ {int size; struct TYPE_8__* next; int /*<<< orphan*/  extent; } ;
typedef  TYPE_2__ base_block_t ;

/* Variables and functions */
 scalar_t__ BASE_AUTO_THP_THRESHOLD ; 
 scalar_t__ BASE_AUTO_THP_THRESHOLD_A0 ; 
 int HUGEPAGE_CEILING (scalar_t__) ; 
 int HUGEPAGE_MASK ; 
 int LG_HUGEPAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ base_get_num_blocks (TYPE_1__*,int) ; 
 scalar_t__ base_ind_get (TYPE_1__*) ; 
 scalar_t__ config_stats ; 
 scalar_t__ extent_bsize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ metadata_thp_auto ; 
 scalar_t__ opt_metadata_thp ; 
 int /*<<< orphan*/  pages_huge (TYPE_2__*,int) ; 

__attribute__((used)) static void
base_auto_thp_switch(tsdn_t *tsdn, base_t *base) {
	assert(opt_metadata_thp == metadata_thp_auto);
	malloc_mutex_assert_owner(tsdn, &base->mtx);
	if (base->auto_thp_switched) {
		return;
	}
	/* Called when adding a new block. */
	bool should_switch;
	if (base_ind_get(base) != 0) {
		should_switch = (base_get_num_blocks(base, true) ==
		    BASE_AUTO_THP_THRESHOLD);
	} else {
		should_switch = (base_get_num_blocks(base, true) ==
		    BASE_AUTO_THP_THRESHOLD_A0);
	}
	if (!should_switch) {
		return;
	}

	base->auto_thp_switched = true;
	assert(!config_stats || base->n_thp == 0);
	/* Make the initial blocks THP lazily. */
	base_block_t *block = base->blocks;
	while (block != NULL) {
		assert((block->size & HUGEPAGE_MASK) == 0);
		pages_huge(block, block->size);
		if (config_stats) {
			base->n_thp += HUGEPAGE_CEILING(block->size -
			    extent_bsize_get(&block->extent)) >> LG_HUGEPAGE;
		}
		block = block->next;
		assert(block == NULL || (base_ind_get(base) == 0));
	}
}