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
struct TYPE_2__ {int (* lock ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_TRY ; 
 TYPE_1__ evthread_lock_fns_ ; 
 int stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline int
EVLOCK_TRY_LOCK_(void *lock)
{
	if (lock && evthread_lock_fns_.lock) {
		int r = evthread_lock_fns_.lock(EVTHREAD_TRY, lock);
		return !r;
	} else {
		/* Locking is disabled either globally or for this thing;
		 * of course we count as having the lock. */
		return 1;
	}
}