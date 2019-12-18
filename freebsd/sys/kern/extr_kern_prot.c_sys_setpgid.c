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
struct setpgid_args {scalar_t__ pgid; scalar_t__ pid; } ;
struct proc {scalar_t__ p_pid; scalar_t__ p_session; int p_flag; struct pgrp* p_pgrp; } ;
struct pgrp {scalar_t__ pg_id; scalar_t__ pg_session; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_PGRP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_EXEC ; 
 scalar_t__ SESS_LEADER (struct proc*) ; 
 int enterpgrp (struct proc*,scalar_t__,struct pgrp*,int /*<<< orphan*/ *) ; 
 int enterthispgrp (struct proc*,struct pgrp*) ; 
 int /*<<< orphan*/  free (struct pgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior (struct proc*) ; 
 struct pgrp* malloc (int,int /*<<< orphan*/ ,int) ; 
 int p_cansee (struct thread*,struct proc*) ; 
 struct proc* pfind (scalar_t__) ; 
 struct pgrp* pgfind (scalar_t__) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
sys_setpgid(struct thread *td, struct setpgid_args *uap)
{
	struct proc *curp = td->td_proc;
	struct proc *targp;	/* target process */
	struct pgrp *pgrp;	/* target pgrp */
	int error;
	struct pgrp *newpgrp;

	if (uap->pgid < 0)
		return (EINVAL);

	error = 0;

	newpgrp = malloc(sizeof(struct pgrp), M_PGRP, M_WAITOK | M_ZERO);

	sx_xlock(&proctree_lock);
	if (uap->pid != 0 && uap->pid != curp->p_pid) {
		if ((targp = pfind(uap->pid)) == NULL) {
			error = ESRCH;
			goto done;
		}
		if (!inferior(targp)) {
			PROC_UNLOCK(targp);
			error = ESRCH;
			goto done;
		}
		if ((error = p_cansee(td, targp))) {
			PROC_UNLOCK(targp);
			goto done;
		}
		if (targp->p_pgrp == NULL ||
		    targp->p_session != curp->p_session) {
			PROC_UNLOCK(targp);
			error = EPERM;
			goto done;
		}
		if (targp->p_flag & P_EXEC) {
			PROC_UNLOCK(targp);
			error = EACCES;
			goto done;
		}
		PROC_UNLOCK(targp);
	} else
		targp = curp;
	if (SESS_LEADER(targp)) {
		error = EPERM;
		goto done;
	}
	if (uap->pgid == 0)
		uap->pgid = targp->p_pid;
	if ((pgrp = pgfind(uap->pgid)) == NULL) {
		if (uap->pgid == targp->p_pid) {
			error = enterpgrp(targp, uap->pgid, newpgrp,
			    NULL);
			if (error == 0)
				newpgrp = NULL;
		} else
			error = EPERM;
	} else {
		if (pgrp == targp->p_pgrp) {
			PGRP_UNLOCK(pgrp);
			goto done;
		}
		if (pgrp->pg_id != targp->p_pid &&
		    pgrp->pg_session != curp->p_session) {
			PGRP_UNLOCK(pgrp);
			error = EPERM;
			goto done;
		}
		PGRP_UNLOCK(pgrp);
		error = enterthispgrp(targp, pgrp);
	}
done:
	sx_xunlock(&proctree_lock);
	KASSERT((error == 0) || (newpgrp != NULL),
	    ("setpgid failed and newpgrp is NULL"));
	if (newpgrp != NULL)
		free(newpgrp, M_PGRP);
	return (error);
}