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
struct thread {int /*<<< orphan*/  td_slpcallout; int /*<<< orphan*/ * td_cpuset; } ;
struct proc {int p_numthreads; scalar_t__ p_exitthreads; } ;

/* Variables and functions */
 struct thread* FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_thread_clean (struct thread*) ; 
 int /*<<< orphan*/  cpuset_rel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_profile_thread_exit (struct thread*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_cow_free (struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_reap () ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
thread_wait(struct proc *p)
{
	struct thread *td;

	mtx_assert(&Giant, MA_NOTOWNED);
	KASSERT(p->p_numthreads == 1, ("multiple threads in thread_wait()"));
	KASSERT(p->p_exitthreads == 0, ("p_exitthreads leaking"));
	td = FIRST_THREAD_IN_PROC(p);
	/* Lock the last thread so we spin until it exits cpu_throw(). */
	thread_lock(td);
	thread_unlock(td);
	lock_profile_thread_exit(td);
	cpuset_rel(td->td_cpuset);
	td->td_cpuset = NULL;
	cpu_thread_clean(td);
	thread_cow_free(td);
	callout_drain(&td->td_slpcallout);
	thread_reap();	/* check for zombie threads etc. */
}