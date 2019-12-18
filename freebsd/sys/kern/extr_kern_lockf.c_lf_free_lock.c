#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sx {int dummy; } ;
struct lockf_entry {scalar_t__ lf_refs; size_t lo_hash; scalar_t__ lo_refs; int lf_flags; int /*<<< orphan*/ * lf_vnode; scalar_t__ lo_vertex; int /*<<< orphan*/  lf_inedges; int /*<<< orphan*/  lf_outedges; struct lockf_entry* lf_owner; } ;
struct lock_owner {scalar_t__ lf_refs; size_t lo_hash; scalar_t__ lo_refs; int lf_flags; int /*<<< orphan*/ * lf_vnode; scalar_t__ lo_vertex; int /*<<< orphan*/  lf_inedges; int /*<<< orphan*/  lf_outedges; struct lock_owner* lf_owner; } ;
struct TYPE_2__ {struct sx lock; } ;

/* Variables and functions */
 int F_REMOTE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct lockf_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LOCKF ; 
 int /*<<< orphan*/  free (struct lockf_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  graph_free_vertex (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* lf_lock_owners ; 
 int /*<<< orphan*/  lf_owner_graph ; 
 struct sx lf_owner_graph_lock ; 
 int /*<<< orphan*/  lo_link ; 
 int lockf_debug ; 
 int /*<<< orphan*/  printf (char*,struct lockf_entry*) ; 
 int /*<<< orphan*/  sx_unlock (struct sx*) ; 
 int /*<<< orphan*/  sx_xlock (struct sx*) ; 
 int /*<<< orphan*/  sx_xunlock (struct sx*) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lf_free_lock(struct lockf_entry *lock)
{
	struct sx *chainlock;

	KASSERT(lock->lf_refs > 0, ("lockf_entry negative ref count %p", lock));
	if (--lock->lf_refs > 0)
		return (0);
	/*
	 * Adjust the lock_owner reference count and
	 * reclaim the entry if this is the last lock
	 * for that owner.
	 */
	struct lock_owner *lo = lock->lf_owner;
	if (lo) {
		KASSERT(LIST_EMPTY(&lock->lf_outedges),
		    ("freeing lock with dependencies"));
		KASSERT(LIST_EMPTY(&lock->lf_inedges),
		    ("freeing lock with dependants"));
		chainlock = &lf_lock_owners[lo->lo_hash].lock;
		sx_xlock(chainlock);
		KASSERT(lo->lo_refs > 0, ("lock owner refcount"));
		lo->lo_refs--;
		if (lo->lo_refs == 0) {
#ifdef LOCKF_DEBUG
			if (lockf_debug & 1)
				printf("lf_free_lock: freeing lock owner %p\n",
				    lo);
#endif
			if (lo->lo_vertex) {
				sx_xlock(&lf_owner_graph_lock);
				graph_free_vertex(&lf_owner_graph,
				    lo->lo_vertex);
				sx_xunlock(&lf_owner_graph_lock);
			}
			LIST_REMOVE(lo, lo_link);
			free(lo, M_LOCKF);
#ifdef LOCKF_DEBUG
			if (lockf_debug & 4)
				printf("Freed lock owner %p\n", lo);
#endif
		}
		sx_unlock(chainlock);
	}
	if ((lock->lf_flags & F_REMOTE) && lock->lf_vnode) {
		vrele(lock->lf_vnode);
		lock->lf_vnode = NULL;
	}
#ifdef LOCKF_DEBUG
	if (lockf_debug & 4)
		printf("Freed lock %p\n", lock);
#endif
	free(lock, M_LOCKF);
	return (1);
}