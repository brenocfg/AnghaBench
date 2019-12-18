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
struct thread {int /*<<< orphan*/  td_sigmask; int /*<<< orphan*/  td_siglist; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_siglist; } ;
struct linux_rt_sigpending_args {int sigsetsize; int /*<<< orphan*/  set; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  lset ;
typedef  int /*<<< orphan*/  l_sigset_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGSETAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSETOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsd_to_linux_sigset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
linux_rt_sigpending(struct thread *td, struct linux_rt_sigpending_args *args)
{
	struct proc *p = td->td_proc;
	sigset_t bset;
	l_sigset_t lset;

	if (args->sigsetsize > sizeof(lset))
		return (EINVAL);
		/* NOT REACHED */

	PROC_LOCK(p);
	bset = p->p_siglist;
	SIGSETOR(bset, td->td_siglist);
	SIGSETAND(bset, td->td_sigmask);
	PROC_UNLOCK(p);
	bsd_to_linux_sigset(&bset, &lset);
	return (copyout(&lset, args->set, args->sigsetsize));
}