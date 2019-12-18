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
struct thread {int td_flags; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_boundary_count; int /*<<< orphan*/  p_suspcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_SLOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int TDF_ALLPROCSUSP ; 
 int TDF_BOUNDARY ; 
 int /*<<< orphan*/  TD_CLR_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  TD_IS_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int setrunnable (struct thread*) ; 

__attribute__((used)) static int
thread_unsuspend_one(struct thread *td, struct proc *p, bool boundary)
{

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	KASSERT(TD_IS_SUSPENDED(td), ("Thread not suspended"));
	TD_CLR_SUSPENDED(td);
	td->td_flags &= ~TDF_ALLPROCSUSP;
	if (td->td_proc == p) {
		PROC_SLOCK_ASSERT(p, MA_OWNED);
		p->p_suspcount--;
		if (boundary && (td->td_flags & TDF_BOUNDARY) != 0) {
			td->td_flags &= ~TDF_BOUNDARY;
			p->p_boundary_count--;
		}
	}
	return (setrunnable(td));
}