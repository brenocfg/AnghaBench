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
struct thread {int td_flags; int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SIGPENDING (struct thread*) ; 
 int TDF_ASTPENDING ; 
 int TDF_NEEDSIGCHK ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
signotify(struct thread *td)
{

	PROC_LOCK_ASSERT(td->td_proc, MA_OWNED);

	if (SIGPENDING(td)) {
		thread_lock(td);
		td->td_flags |= TDF_NEEDSIGCHK | TDF_ASTPENDING;
		thread_unlock(td);
	}
}