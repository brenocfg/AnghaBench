#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_5__ {int /*<<< orphan*/  init_lock; } ;
typedef  TYPE_1__ rtree_t ;
typedef  int /*<<< orphan*/  rtree_node_elm_t ;
typedef  int /*<<< orphan*/  atomic_p_t ;
struct TYPE_6__ {int bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  ATOMIC_RELEASE ; 
 int ZU (int) ; 
 int /*<<< orphan*/ * atomic_load_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* rtree_levels ; 
 int /*<<< orphan*/ * rtree_node_alloc (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static rtree_node_elm_t *
rtree_node_init(tsdn_t *tsdn, rtree_t *rtree, unsigned level,
    atomic_p_t *elmp) {
	malloc_mutex_lock(tsdn, &rtree->init_lock);
	/*
	 * If *elmp is non-null, then it was initialized with the init lock
	 * held, so we can get by with 'relaxed' here.
	 */
	rtree_node_elm_t *node = atomic_load_p(elmp, ATOMIC_RELAXED);
	if (node == NULL) {
		node = rtree_node_alloc(tsdn, rtree, ZU(1) <<
		    rtree_levels[level].bits);
		if (node == NULL) {
			malloc_mutex_unlock(tsdn, &rtree->init_lock);
			return NULL;
		}
		/*
		 * Even though we hold the lock, a later reader might not; we
		 * need release semantics.
		 */
		atomic_store_p(elmp, node, ATOMIC_RELEASE);
	}
	malloc_mutex_unlock(tsdn, &rtree->init_lock);

	return node;
}