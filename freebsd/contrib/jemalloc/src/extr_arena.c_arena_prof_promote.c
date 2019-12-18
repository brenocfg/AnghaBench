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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_3__ {int /*<<< orphan*/  prof_accum; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 size_t LARGE_MINCLASS ; 
 size_t SMALL_MAXCLASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 TYPE_1__* extent_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_szind_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extents_rtree ; 
 size_t isalloc (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  prof_accum_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * rtree_extent_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t,int) ; 
 int /*<<< orphan*/  rtree_szind_slab_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
arena_prof_promote(tsdn_t *tsdn, const void *ptr, size_t usize) {
	cassert(config_prof);
	assert(ptr != NULL);
	assert(isalloc(tsdn, ptr) == LARGE_MINCLASS);
	assert(usize <= SMALL_MAXCLASS);

	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	extent_t *extent = rtree_extent_read(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)ptr, true);
	arena_t *arena = extent_arena_get(extent);

	szind_t szind = sz_size2index(usize);
	extent_szind_set(extent, szind);
	rtree_szind_slab_update(tsdn, &extents_rtree, rtree_ctx, (uintptr_t)ptr,
	    szind, false);

	prof_accum_cancel(tsdn, &arena->prof_accum, usize);

	assert(isalloc(tsdn, ptr) == usize);
}