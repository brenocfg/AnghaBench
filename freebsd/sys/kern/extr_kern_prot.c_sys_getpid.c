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
struct thread {int /*<<< orphan*/ * td_retval; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;
struct getpid_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_AOUT ; 
 scalar_t__ SV_PROC_FLAG (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_getppid (struct thread*) ; 

int
sys_getpid(struct thread *td, struct getpid_args *uap)
{
	struct proc *p = td->td_proc;

	td->td_retval[0] = p->p_pid;
#if defined(COMPAT_43)
	if (SV_PROC_FLAG(p, SV_AOUT))
		td->td_retval[1] = kern_getppid(td);
#endif
	return (0);
}