#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct thread {TYPE_2__* td_ucred; TYPE_1__* td_proc; } ;
struct proc {int dummy; } ;
struct kill_args {int pid; scalar_t__ signum; } ;
struct TYPE_9__ {int ksi_pid; int /*<<< orphan*/  ksi_uid; int /*<<< orphan*/  ksi_code; scalar_t__ ksi_signo; } ;
typedef  TYPE_3__ ksiginfo_t ;
struct TYPE_8__ {int /*<<< orphan*/  cr_ruid; } ;
struct TYPE_7__ {int p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_PID (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_PROCESS (struct proc*) ; 
 int /*<<< orphan*/  AUDIT_ARG_SIGNUM (scalar_t__) ; 
 int ECAPMODE ; 
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SI_USER ; 
 scalar_t__ _SIG_MAXSIG ; 
 int killpg1 (struct thread*,scalar_t__,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_3__*) ; 
 int p_cansignal (struct thread*,struct proc*,scalar_t__) ; 
 struct proc* pfind_any (int) ; 
 int /*<<< orphan*/  pksignal (struct proc*,scalar_t__,TYPE_3__*) ; 

int
sys_kill(struct thread *td, struct kill_args *uap)
{
	ksiginfo_t ksi;
	struct proc *p;
	int error;

	/*
	 * A process in capability mode can send signals only to himself.
	 * The main rationale behind this is that abort(3) is implemented as
	 * kill(getpid(), SIGABRT).
	 */
	if (IN_CAPABILITY_MODE(td) && uap->pid != td->td_proc->p_pid)
		return (ECAPMODE);

	AUDIT_ARG_SIGNUM(uap->signum);
	AUDIT_ARG_PID(uap->pid);
	if ((u_int)uap->signum > _SIG_MAXSIG)
		return (EINVAL);

	ksiginfo_init(&ksi);
	ksi.ksi_signo = uap->signum;
	ksi.ksi_code = SI_USER;
	ksi.ksi_pid = td->td_proc->p_pid;
	ksi.ksi_uid = td->td_ucred->cr_ruid;

	if (uap->pid > 0) {
		/* kill single process */
		if ((p = pfind_any(uap->pid)) == NULL)
			return (ESRCH);
		AUDIT_ARG_PROCESS(p);
		error = p_cansignal(td, p, uap->signum);
		if (error == 0 && uap->signum)
			pksignal(p, uap->signum, &ksi);
		PROC_UNLOCK(p);
		return (error);
	}
	switch (uap->pid) {
	case -1:		/* broadcast signal */
		return (killpg1(td, uap->signum, 0, 1, &ksi));
	case 0:			/* signal own process group */
		return (killpg1(td, uap->signum, 0, 0, &ksi));
	default:		/* negative explicit process group */
		return (killpg1(td, uap->signum, -uap->pid, 0, &ksi));
	}
	/* NOTREACHED */
}