#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {scalar_t__ td_tid; struct proc* td_proc; } ;
struct rtprio_thread_args {int function; scalar_t__ lwpid; int /*<<< orphan*/  rtp; } ;
struct rtprio {int /*<<< orphan*/  type; } ;
struct proc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  PRIV_SCHED_RTPRIO ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
#define  RTP_LOOKUP 129 
 int /*<<< orphan*/  RTP_PRIO_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTP_PRIO_IDLE ; 
 int /*<<< orphan*/  RTP_PRIO_REALTIME ; 
#define  RTP_SET 128 
 int copyin (int /*<<< orphan*/ ,struct rtprio*,int) ; 
 int copyout (struct rtprio*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* curproc ; 
 int p_cansched (struct thread*,struct proc*) ; 
 int p_cansee (struct thread*,struct proc*) ; 
 int /*<<< orphan*/  pri_to_rtp (struct thread*,struct rtprio*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int rtp_to_pri (struct rtprio*,struct thread*) ; 
 struct thread* tdfind (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unprivileged_idprio ; 

int
sys_rtprio_thread(struct thread *td, struct rtprio_thread_args *uap)
{
	struct proc *p;
	struct rtprio rtp;
	struct thread *td1;
	int cierror, error;

	/* Perform copyin before acquiring locks if needed. */
	if (uap->function == RTP_SET)
		cierror = copyin(uap->rtp, &rtp, sizeof(struct rtprio));
	else
		cierror = 0;

	if (uap->lwpid == 0 || uap->lwpid == td->td_tid) {
		p = td->td_proc;
		td1 = td;
		PROC_LOCK(p);
	} else {
		/* Only look up thread in current process */
		td1 = tdfind(uap->lwpid, curproc->p_pid);
		if (td1 == NULL)
			return (ESRCH);
		p = td1->td_proc;
	}

	switch (uap->function) {
	case RTP_LOOKUP:
		if ((error = p_cansee(td, p)))
			break;
		pri_to_rtp(td1, &rtp);
		PROC_UNLOCK(p);
		return (copyout(&rtp, uap->rtp, sizeof(struct rtprio)));
	case RTP_SET:
		if ((error = p_cansched(td, p)) || (error = cierror))
			break;

		/* Disallow setting rtprio in most cases if not superuser. */

		/*
		 * Realtime priority has to be restricted for reasons which
		 * should be obvious.  However, for idleprio processes, there is
		 * a potential for system deadlock if an idleprio process gains
		 * a lock on a resource that other processes need (and the
		 * idleprio process can't run due to a CPU-bound normal
		 * process).  Fix me!  XXX
		 *
		 * This problem is not only related to idleprio process.
		 * A user level program can obtain a file lock and hold it
		 * indefinitely.  Additionally, without idleprio processes it is
		 * still conceivable that a program with low priority will never
		 * get to run.  In short, allowing this feature might make it
		 * easier to lock a resource indefinitely, but it is not the
		 * only thing that makes it possible.
		 */
		if (RTP_PRIO_BASE(rtp.type) == RTP_PRIO_REALTIME ||
		    (RTP_PRIO_BASE(rtp.type) == RTP_PRIO_IDLE &&
		    unprivileged_idprio == 0)) {
			error = priv_check(td, PRIV_SCHED_RTPRIO);
			if (error)
				break;
		}
		error = rtp_to_pri(&rtp, td1);
		break;
	default:
		error = EINVAL;
		break;
	}
	PROC_UNLOCK(p);
	return (error);
}