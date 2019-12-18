#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sq_signals; } ;
struct thread {TYPE_2__ td_sigqueue; struct proc* td_proc; } ;
struct sigpending_args {int /*<<< orphan*/  set; } ;
struct TYPE_3__ {int /*<<< orphan*/  sq_signals; } ;
struct proc {TYPE_1__ p_sigqueue; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGSETOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
sys_sigpending(struct thread *td, struct sigpending_args *uap)
{
	struct proc *p = td->td_proc;
	sigset_t pending;

	PROC_LOCK(p);
	pending = p->p_sigqueue.sq_signals;
	SIGSETOR(pending, td->td_sigqueue.sq_signals);
	PROC_UNLOCK(p);
	return (copyout(&pending, uap->set, sizeof(sigset_t)));
}