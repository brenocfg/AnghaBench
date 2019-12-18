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
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_3__ {int /*<<< orphan*/  extent_avail_mtx; int /*<<< orphan*/  extent_avail; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * base_alloc_extent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extent_avail_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_avail_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

extent_t *
extent_alloc(tsdn_t *tsdn, arena_t *arena) {
	malloc_mutex_lock(tsdn, &arena->extent_avail_mtx);
	extent_t *extent = extent_avail_first(&arena->extent_avail);
	if (extent == NULL) {
		malloc_mutex_unlock(tsdn, &arena->extent_avail_mtx);
		return base_alloc_extent(tsdn, arena->base);
	}
	extent_avail_remove(&arena->extent_avail, extent);
	malloc_mutex_unlock(tsdn, &arena->extent_avail_mtx);
	return extent;
}