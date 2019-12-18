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
struct futex_lock {int dummy; } ;
struct futex_condvar {scalar_t__ fc_waitcount; int /*<<< orphan*/  fc_address; struct futex_lock* fc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct futex_condvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_FUTEX ; 
 int /*<<< orphan*/  fc_next ; 
 int /*<<< orphan*/  free (struct futex_condvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futex_address_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  futex_condvar_assert (struct futex_condvar*) ; 
 int /*<<< orphan*/  futex_lock_release (struct futex_lock*) ; 

__attribute__((used)) static void
futex_condvar_release(struct futex_condvar *fc)
{
	struct futex_lock *fl;

	futex_condvar_assert(fc);
	fl = fc->fc_lock;
	if (fc->fc_waitcount == 0) {
		/* Condition variable has no waiters. Deallocate it. */
		futex_address_free(&fc->fc_address);
		LIST_REMOVE(fc, fc_next);
		free(fc, M_FUTEX);
	}
	futex_lock_release(fl);
}