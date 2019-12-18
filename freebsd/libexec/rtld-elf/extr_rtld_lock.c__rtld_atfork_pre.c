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
struct TYPE_3__ {int lockstate; } ;
typedef  TYPE_1__ RtldLockState ;

/* Variables and functions */
 int /*<<< orphan*/  rtld_bind_lock ; 
 int /*<<< orphan*/  rtld_phdr_lock ; 
 int /*<<< orphan*/  wlock_acquire (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
_rtld_atfork_pre(int *locks)
{
	RtldLockState ls[2];

	if (locks == NULL)
		return;

	/*
	 * Warning: this did not worked well with the rtld compat
	 * locks above, when the thread signal mask was corrupted (set
	 * to all signals blocked) if two locks were taken
	 * simultaneously in the write mode.  The caller of the
	 * _rtld_atfork_pre() must provide the working implementation
	 * of the locks anyway, and libthr locks are fine.
	 */
	wlock_acquire(rtld_phdr_lock, &ls[0]);
	wlock_acquire(rtld_bind_lock, &ls[1]);

	/* XXXKIB: I am really sorry for this. */
	locks[0] = ls[1].lockstate;
	locks[2] = ls[0].lockstate;
}