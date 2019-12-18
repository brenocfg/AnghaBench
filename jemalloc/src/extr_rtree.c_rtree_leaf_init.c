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
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_5__ {int /*<<< orphan*/  init_lock; } ;
typedef  TYPE_1__ rtree_t ;
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;
typedef  int /*<<< orphan*/  atomic_p_t ;
struct TYPE_6__ {int bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  ATOMIC_RELEASE ; 
 int RTREE_HEIGHT ; 
 int ZU (int) ; 
 int /*<<< orphan*/ * atomic_load_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtree_leaf_alloc (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_2__* rtree_levels ; 

__attribute__((used)) static rtree_leaf_elm_t *
rtree_leaf_init(tsdn_t *tsdn, rtree_t *rtree, atomic_p_t *elmp) {
	malloc_mutex_lock(tsdn, &rtree->init_lock);
	/*
	 * If *elmp is non-null, then it was initialized with the init lock
	 * held, so we can get by with 'relaxed' here.
	 */
	rtree_leaf_elm_t *leaf = atomic_load_p(elmp, ATOMIC_RELAXED);
	if (leaf == NULL) {
		leaf = rtree_leaf_alloc(tsdn, rtree, ZU(1) <<
		    rtree_levels[RTREE_HEIGHT-1].bits);
		if (leaf == NULL) {
			malloc_mutex_unlock(tsdn, &rtree->init_lock);
			return NULL;
		}
		/*
		 * Even though we hold the lock, a later reader might not; we
		 * need release semantics.
		 */
		atomic_store_p(elmp, leaf, ATOMIC_RELEASE);
	}
	malloc_mutex_unlock(tsdn, &rtree->init_lock);

	return leaf;
}