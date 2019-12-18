#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct thread {int dummy; } ;
struct rusage {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;
struct proc {scalar_t__ p_state; scalar_t__ p_sigparent; TYPE_4__* p_stats; struct rusage p_ru; TYPE_3__* p_ucred; int /*<<< orphan*/  p_pid; void* p_xexit; int /*<<< orphan*/  p_xsig; TYPE_1__* p_session; int /*<<< orphan*/  p_pgid; int /*<<< orphan*/ * p_procdesc; } ;
struct __wrusage {struct rusage wru_children; struct rusage wru_self; } ;
struct TYPE_12__ {int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; void* si_status; int /*<<< orphan*/  si_code; scalar_t__ si_signo; scalar_t__ si_errno; } ;
typedef  TYPE_5__ siginfo_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int idtype_t ;
typedef  scalar_t__ id_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_11__ {struct rusage p_cru; } ;
struct TYPE_10__ {int /*<<< orphan*/  cr_uid; TYPE_2__* cr_prison; int /*<<< orphan*/  cr_gid; } ;
struct TYPE_9__ {int pr_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_DUMPED ; 
 int /*<<< orphan*/  CLD_EXITED ; 
 int /*<<< orphan*/  CLD_KILLED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ PRS_ZOMBIE ; 
#define  P_ALL 134 
#define  P_GID 133 
#define  P_JAILID 132 
#define  P_PGID 131 
#define  P_PID 130 
#define  P_SID 129 
#define  P_UID 128 
 int /*<<< orphan*/  SA_XLOCKED ; 
 scalar_t__ SIGCHLD ; 
 scalar_t__ WCOREDUMP (int /*<<< orphan*/ ) ; 
 int WEXITED ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 int WLINUXCLONE ; 
 void* WTERMSIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  calccru (struct proc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calcru (struct proc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ p_canwait (struct thread*,struct proc*) ; 
 int /*<<< orphan*/  proc_reap (struct thread*,struct proc*,int*,int) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proc_to_reap(struct thread *td, struct proc *p, idtype_t idtype, id_t id,
    int *status, int options, struct __wrusage *wrusage, siginfo_t *siginfo,
    int check_only)
{
	struct rusage *rup;

	sx_assert(&proctree_lock, SA_XLOCKED);

	PROC_LOCK(p);

	switch (idtype) {
	case P_ALL:
		if (p->p_procdesc != NULL) {
			PROC_UNLOCK(p);
			return (0);
		}
		break;
	case P_PID:
		if (p->p_pid != (pid_t)id) {
			PROC_UNLOCK(p);
			return (0);
		}
		break;
	case P_PGID:
		if (p->p_pgid != (pid_t)id) {
			PROC_UNLOCK(p);
			return (0);
		}
		break;
	case P_SID:
		if (p->p_session->s_sid != (pid_t)id) {
			PROC_UNLOCK(p);
			return (0);
		}
		break;
	case P_UID:
		if (p->p_ucred->cr_uid != (uid_t)id) {
			PROC_UNLOCK(p);
			return (0);
		}
		break;
	case P_GID:
		if (p->p_ucred->cr_gid != (gid_t)id) {
			PROC_UNLOCK(p);
			return (0);
		}
		break;
	case P_JAILID:
		if (p->p_ucred->cr_prison->pr_id != (int)id) {
			PROC_UNLOCK(p);
			return (0);
		}
		break;
	/*
	 * It seems that the thread structures get zeroed out
	 * at process exit.  This makes it impossible to
	 * support P_SETID, P_CID or P_CPUID.
	 */
	default:
		PROC_UNLOCK(p);
		return (0);
	}

	if (p_canwait(td, p)) {
		PROC_UNLOCK(p);
		return (0);
	}

	if (((options & WEXITED) == 0) && (p->p_state == PRS_ZOMBIE)) {
		PROC_UNLOCK(p);
		return (0);
	}

	/*
	 * This special case handles a kthread spawned by linux_clone
	 * (see linux_misc.c).  The linux_wait4 and linux_waitpid
	 * functions need to be able to distinguish between waiting
	 * on a process and waiting on a thread.  It is a thread if
	 * p_sigparent is not SIGCHLD, and the WLINUXCLONE option
	 * signifies we want to wait for threads and not processes.
	 */
	if ((p->p_sigparent != SIGCHLD) ^
	    ((options & WLINUXCLONE) != 0)) {
		PROC_UNLOCK(p);
		return (0);
	}

	if (siginfo != NULL) {
		bzero(siginfo, sizeof(*siginfo));
		siginfo->si_errno = 0;

		/*
		 * SUSv4 requires that the si_signo value is always
		 * SIGCHLD. Obey it despite the rfork(2) interface
		 * allows to request other signal for child exit
		 * notification.
		 */
		siginfo->si_signo = SIGCHLD;

		/*
		 *  This is still a rough estimate.  We will fix the
		 *  cases TRAPPED, STOPPED, and CONTINUED later.
		 */
		if (WCOREDUMP(p->p_xsig)) {
			siginfo->si_code = CLD_DUMPED;
			siginfo->si_status = WTERMSIG(p->p_xsig);
		} else if (WIFSIGNALED(p->p_xsig)) {
			siginfo->si_code = CLD_KILLED;
			siginfo->si_status = WTERMSIG(p->p_xsig);
		} else {
			siginfo->si_code = CLD_EXITED;
			siginfo->si_status = p->p_xexit;
		}

		siginfo->si_pid = p->p_pid;
		siginfo->si_uid = p->p_ucred->cr_uid;

		/*
		 * The si_addr field would be useful additional
		 * detail, but apparently the PC value may be lost
		 * when we reach this point.  bzero() above sets
		 * siginfo->si_addr to NULL.
		 */
	}

	/*
	 * There should be no reason to limit resources usage info to
	 * exited processes only.  A snapshot about any resources used
	 * by a stopped process may be exactly what is needed.
	 */
	if (wrusage != NULL) {
		rup = &wrusage->wru_self;
		*rup = p->p_ru;
		PROC_STATLOCK(p);
		calcru(p, &rup->ru_utime, &rup->ru_stime);
		PROC_STATUNLOCK(p);

		rup = &wrusage->wru_children;
		*rup = p->p_stats->p_cru;
		calccru(p, &rup->ru_utime, &rup->ru_stime);
	}

	if (p->p_state == PRS_ZOMBIE && !check_only) {
		proc_reap(td, p, status, options);
		return (-1);
	}
	return (1);
}