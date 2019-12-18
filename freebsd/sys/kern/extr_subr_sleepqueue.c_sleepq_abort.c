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
struct thread {int td_flags; int td_intrval; void* td_wchan; scalar_t__ td_name; TYPE_1__* td_proc; } ;
struct sleepqueue {int dummy; } ;
struct TYPE_2__ {scalar_t__ p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,void*,long,void*) ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  KTR_PROC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int TDF_SINTR ; 
 int TDF_SLEEPABORT ; 
 int TDF_TIMEOUT ; 
 int /*<<< orphan*/  TD_IS_SLEEPING (struct thread*) ; 
 int TD_ON_SLEEPQ (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 struct sleepqueue* sleepq_lookup (void*) ; 
 int sleepq_resume_thread (struct sleepqueue*,struct thread*,int /*<<< orphan*/ ) ; 

int
sleepq_abort(struct thread *td, int intrval)
{
	struct sleepqueue *sq;
	void *wchan;

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	MPASS(TD_ON_SLEEPQ(td));
	MPASS(td->td_flags & TDF_SINTR);
	MPASS(intrval == EINTR || intrval == ERESTART);

	/*
	 * If the TDF_TIMEOUT flag is set, just leave. A
	 * timeout is scheduled anyhow.
	 */
	if (td->td_flags & TDF_TIMEOUT)
		return (0);

	CTR3(KTR_PROC, "sleepq_abort: thread %p (pid %ld, %s)",
	    (void *)td, (long)td->td_proc->p_pid, (void *)td->td_name);
	td->td_intrval = intrval;
	td->td_flags |= TDF_SLEEPABORT;
	/*
	 * If the thread has not slept yet it will find the signal in
	 * sleepq_catch_signals() and call sleepq_resume_thread.  Otherwise
	 * we have to do it here.
	 */
	if (!TD_IS_SLEEPING(td))
		return (0);
	wchan = td->td_wchan;
	MPASS(wchan != NULL);
	sq = sleepq_lookup(wchan);
	MPASS(sq != NULL);

	/* Thread is asleep on sleep queue sq, so wake it up. */
	return (sleepq_resume_thread(sq, td, 0));
}