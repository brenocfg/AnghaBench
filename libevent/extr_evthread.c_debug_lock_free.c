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
struct debug_lock {int count; unsigned int locktype; int signature; int /*<<< orphan*/ * lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int DEBUG_LOCK_SIG ; 
 int EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  mm_free (struct debug_lock*) ; 
 TYPE_1__ original_lock_fns_ ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
debug_lock_free(void *lock_, unsigned locktype)
{
	struct debug_lock *lock = lock_;
	EVUTIL_ASSERT(lock->count == 0);
	EVUTIL_ASSERT(locktype == lock->locktype);
	EVUTIL_ASSERT(DEBUG_LOCK_SIG == lock->signature);
	if (original_lock_fns_.free) {
		original_lock_fns_.free(lock->lock,
		    lock->locktype|EVTHREAD_LOCKTYPE_RECURSIVE);
	}
	lock->lock = NULL;
	lock->count = -100;
	lock->signature = 0x12300fda;
	mm_free(lock);
}