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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _thr_umutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* extra ; 
 int initialized ; 
 int spinlock_count ; 
 int /*<<< orphan*/  spinlock_static_lock ; 

void
_thr_spinlock_init(void)
{
	int i;

	_thr_umutex_init(&spinlock_static_lock);
	if (initialized != 0) {
		/*
		 * called after fork() to reset state of libc spin locks,
		 * it is not quite right since libc may be in inconsistent
		 * state, resetting the locks to allow current thread to be
		 * able to hold them may not help things too much, but
		 * anyway, we do our best.
		 * it is better to do pthread_atfork in libc.
		 */
		for (i = 0; i < spinlock_count; i++)
			_thr_umutex_init(&extra[i].lock);
	} else {
		initialized = 1;
	}
}