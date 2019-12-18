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
struct thread {int td_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int SIGDEFERSTOP_VAL_NCHG ; 
 int TDF_SBDRY ; 
 int TDF_SEINTR ; 
 int TDF_SERESTART ; 
 struct thread* curthread ; 
 int sigdeferstop_curr_flags (int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
sigallowstop_impl(int prev)
{
	struct thread *td;
	int cflags;

	KASSERT(prev != SIGDEFERSTOP_VAL_NCHG, ("failed sigallowstop"));
	KASSERT((prev & ~(TDF_SBDRY | TDF_SEINTR | TDF_SERESTART)) == 0,
	    ("sigallowstop: incorrect previous mode %x", prev));
	td = curthread;
	cflags = sigdeferstop_curr_flags(td->td_flags);
	if (cflags != prev) {
		thread_lock(td);
		td->td_flags = (td->td_flags & ~cflags) | prev;
		thread_unlock(td);
	}
}