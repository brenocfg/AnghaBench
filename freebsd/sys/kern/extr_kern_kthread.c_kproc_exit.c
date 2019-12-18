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
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  exit1 (struct thread*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initproc ; 
 int /*<<< orphan*/  proc_reparent (struct proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct proc*) ; 

void
kproc_exit(int ecode)
{
	struct thread *td;
	struct proc *p;

	td = curthread;
	p = td->td_proc;

	/*
	 * Reparent curthread from proc0 to init so that the zombie
	 * is harvested.
	 */
	sx_xlock(&proctree_lock);
	PROC_LOCK(p);
	proc_reparent(p, initproc, true);
	PROC_UNLOCK(p);
	sx_xunlock(&proctree_lock);

	/*
	 * Wakeup anyone waiting for us to exit.
	 */
	wakeup(p);

	/* Buh-bye! */
	exit1(td, ecode, 0);
}