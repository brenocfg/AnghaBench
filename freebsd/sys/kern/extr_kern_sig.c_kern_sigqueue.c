#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union sigval {int dummy; } sigval ;
typedef  scalar_t__ u_int ;
struct thread {TYPE_2__* td_ucred; TYPE_1__* td_proc; } ;
struct proc {int dummy; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_8__ {int ksi_signo; union sigval ksi_value; int /*<<< orphan*/  ksi_uid; int /*<<< orphan*/  ksi_pid; int /*<<< orphan*/  ksi_code; int /*<<< orphan*/  ksi_flags; } ;
typedef  TYPE_3__ ksiginfo_t ;
struct TYPE_7__ {int /*<<< orphan*/  cr_ruid; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  KSI_SIGQ ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SI_QUEUE ; 
 scalar_t__ _SIG_MAXSIG ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_3__*) ; 
 int p_cansignal (struct thread*,struct proc*,int) ; 
 struct proc* pfind_any (scalar_t__) ; 
 int pksignal (struct proc*,int,TYPE_3__*) ; 

int
kern_sigqueue(struct thread *td, pid_t pid, int signum, union sigval *value)
{
	ksiginfo_t ksi;
	struct proc *p;
	int error;

	if ((u_int)signum > _SIG_MAXSIG)
		return (EINVAL);

	/*
	 * Specification says sigqueue can only send signal to
	 * single process.
	 */
	if (pid <= 0)
		return (EINVAL);

	if ((p = pfind_any(pid)) == NULL)
		return (ESRCH);
	error = p_cansignal(td, p, signum);
	if (error == 0 && signum != 0) {
		ksiginfo_init(&ksi);
		ksi.ksi_flags = KSI_SIGQ;
		ksi.ksi_signo = signum;
		ksi.ksi_code = SI_QUEUE;
		ksi.ksi_pid = td->td_proc->p_pid;
		ksi.ksi_uid = td->td_ucred->cr_ruid;
		ksi.ksi_value = *value;
		error = pksignal(p, ksi.ksi_signo, &ksi);
	}
	PROC_UNLOCK(p);
	return (error);
}