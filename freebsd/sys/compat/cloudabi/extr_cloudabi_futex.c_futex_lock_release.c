#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct futex_lock {scalar_t__ fl_waitcount; scalar_t__ fl_owner; int /*<<< orphan*/  fl_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct futex_lock*,int /*<<< orphan*/ ) ; 
 scalar_t__ LOCK_UNMANAGED ; 
 int /*<<< orphan*/  M_FUTEX ; 
 int /*<<< orphan*/  fl_next ; 
 int /*<<< orphan*/  free (struct futex_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futex_address_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  futex_global_lock ; 
 int /*<<< orphan*/  futex_lock_assert (struct futex_lock*) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
futex_lock_release(struct futex_lock *fl)
{

	futex_lock_assert(fl);
	if (fl->fl_waitcount == 0) {
		/* Lock object is unreferenced. Deallocate it. */
		KASSERT(fl->fl_owner == LOCK_UNMANAGED,
		    ("Attempted to free a managed lock"));
		futex_address_free(&fl->fl_address);
		LIST_REMOVE(fl, fl_next);
		free(fl, M_FUTEX);
	}
	sx_xunlock(&futex_global_lock);
}