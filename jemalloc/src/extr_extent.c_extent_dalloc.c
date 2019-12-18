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
struct TYPE_3__ {int /*<<< orphan*/  extent_avail_mtx; int /*<<< orphan*/  extent_avail_cnt; int /*<<< orphan*/  extent_avail; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  atomic_fetch_add_zu (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_avail_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
extent_dalloc(tsdn_t *tsdn, arena_t *arena, extent_t *extent) {
	malloc_mutex_lock(tsdn, &arena->extent_avail_mtx);
	extent_avail_insert(&arena->extent_avail, extent);
	atomic_fetch_add_zu(&arena->extent_avail_cnt, 1, ATOMIC_RELAXED);
	malloc_mutex_unlock(tsdn, &arena->extent_avail_mtx);
}