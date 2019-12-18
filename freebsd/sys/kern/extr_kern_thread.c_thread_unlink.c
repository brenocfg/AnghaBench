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
struct thread {int /*<<< orphan*/  td_epochs; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_numthreads; int /*<<< orphan*/  p_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  td_plist ; 

void
thread_unlink(struct thread *td)
{
	struct proc *p = td->td_proc;

	PROC_LOCK_ASSERT(p, MA_OWNED);
#ifdef EPOCH_TRACE
	MPASS(SLIST_EMPTY(&td->td_epochs));
#endif

	TAILQ_REMOVE(&p->p_threads, td, td_plist);
	p->p_numthreads--;
	/* could clear a few other things here */
	/* Must  NOT clear links to proc! */
}