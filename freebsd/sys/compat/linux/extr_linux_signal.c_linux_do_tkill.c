#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;
struct TYPE_4__ {scalar_t__ ksi_signo; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_PROCESS (struct proc*) ; 
 int /*<<< orphan*/  AUDIT_ARG_SIGNUM (scalar_t__) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int p_cansignal (struct thread*,struct proc*,scalar_t__) ; 
 int /*<<< orphan*/  tdksignal (struct thread*,scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static int
linux_do_tkill(struct thread *td, struct thread *tdt, ksiginfo_t *ksi)
{
	struct proc *p;
	int error;

	p = tdt->td_proc;
	AUDIT_ARG_SIGNUM(ksi->ksi_signo);
	AUDIT_ARG_PID(p->p_pid);
	AUDIT_ARG_PROCESS(p);

	error = p_cansignal(td, p, ksi->ksi_signo);
	if (error != 0 || ksi->ksi_signo == 0)
		goto out;

	tdksignal(tdt, ksi->ksi_signo, ksi);

out:
	PROC_UNLOCK(p);
	return (error);
}