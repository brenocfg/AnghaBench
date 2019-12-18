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
struct ucred {scalar_t__ cr_ruid; scalar_t__ cr_uid; } ;
struct proc {int p_flag; TYPE_1__* p_ucred; } ;
struct TYPE_4__ {scalar_t__ cr_ruid; scalar_t__ cr_svuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PRIV_SIGNAL_DIFFCRED ; 
 int /*<<< orphan*/  PRIV_SIGNAL_SUGID ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int P_SUGID ; 
#define  SIGALRM 138 
#define  SIGHUP 137 
#define  SIGINT 136 
#define  SIGKILL 135 
#define  SIGSTOP 134 
#define  SIGTERM 133 
#define  SIGTSTP 132 
#define  SIGTTIN 131 
#define  SIGTTOU 130 
#define  SIGUSR1 129 
#define  SIGUSR2 128 
 scalar_t__ conservative_signals ; 
 int cr_canseeothergids (struct ucred*,TYPE_1__*) ; 
 int cr_canseeotheruids (struct ucred*,TYPE_1__*) ; 
 int mac_proc_check_signal (struct ucred*,struct proc*,int) ; 
 int prison_check (struct ucred*,TYPE_1__*) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

int
cr_cansignal(struct ucred *cred, struct proc *proc, int signum)
{
	int error;

	PROC_LOCK_ASSERT(proc, MA_OWNED);
	/*
	 * Jail semantics limit the scope of signalling to proc in the
	 * same jail as cred, if cred is in jail.
	 */
	error = prison_check(cred, proc->p_ucred);
	if (error)
		return (error);
#ifdef MAC
	if ((error = mac_proc_check_signal(cred, proc, signum)))
		return (error);
#endif
	if ((error = cr_canseeotheruids(cred, proc->p_ucred)))
		return (error);
	if ((error = cr_canseeothergids(cred, proc->p_ucred)))
		return (error);

	/*
	 * UNIX signal semantics depend on the status of the P_SUGID
	 * bit on the target process.  If the bit is set, then additional
	 * restrictions are placed on the set of available signals.
	 */
	if (conservative_signals && (proc->p_flag & P_SUGID)) {
		switch (signum) {
		case 0:
		case SIGKILL:
		case SIGINT:
		case SIGTERM:
		case SIGALRM:
		case SIGSTOP:
		case SIGTTIN:
		case SIGTTOU:
		case SIGTSTP:
		case SIGHUP:
		case SIGUSR1:
		case SIGUSR2:
			/*
			 * Generally, permit job and terminal control
			 * signals.
			 */
			break;
		default:
			/* Not permitted without privilege. */
			error = priv_check_cred(cred, PRIV_SIGNAL_SUGID);
			if (error)
				return (error);
		}
	}

	/*
	 * Generally, the target credential's ruid or svuid must match the
	 * subject credential's ruid or euid.
	 */
	if (cred->cr_ruid != proc->p_ucred->cr_ruid &&
	    cred->cr_ruid != proc->p_ucred->cr_svuid &&
	    cred->cr_uid != proc->p_ucred->cr_ruid &&
	    cred->cr_uid != proc->p_ucred->cr_svuid) {
		error = priv_check_cred(cred, PRIV_SIGNAL_DIFFCRED);
		if (error)
			return (error);
	}

	return (0);
}