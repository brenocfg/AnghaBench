#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct proc {int p_flag; struct proc* p_pptr; int /*<<< orphan*/  p_pid; } ;
struct cdev {int dummy; } ;
struct TYPE_3__ {int dofhp_gen; int /*<<< orphan*/  dofhp_pid; int /*<<< orphan*/  dofhp_dof; } ;
typedef  TYPE_1__ dof_helper_t ;
typedef  int /*<<< orphan*/  dof_hdr_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  DTRACEHIOC_ADDDOF 129 
#define  DTRACEHIOC_REMOVE 128 
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  PRELE (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  P_SHOULDSTOP (struct proc*) ; 
 int P_TRACED ; 
 int P_WEXIT ; 
 int /*<<< orphan*/  _PHOLD (struct proc*) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/ * dtrace_dof_copyin (uintptr_t,int*) ; 
 int /*<<< orphan*/ * dtrace_dof_copyin_proc (struct proc*,uintptr_t,int*) ; 
 int dtrace_helper_destroygen (int /*<<< orphan*/ *,int) ; 
 int dtrace_helper_slurp (int /*<<< orphan*/ *,TYPE_1__*,struct proc*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 struct proc* pfind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_ioctl_helper(struct cdev *dev, u_long cmd, caddr_t addr, int flags,
    struct thread *td)
{
	struct proc *p;
	dof_helper_t *dhp;
	dof_hdr_t *dof;
	int rval;

	dhp = NULL;
	dof = NULL;
	rval = 0;
	switch (cmd) {
	case DTRACEHIOC_ADDDOF:
		dhp = (dof_helper_t *)addr;
		addr = (caddr_t)(uintptr_t)dhp->dofhp_dof;
		p = curproc;
		if (p->p_pid == dhp->dofhp_pid) {
			dof = dtrace_dof_copyin((uintptr_t)addr, &rval);
		} else {
			p = pfind(dhp->dofhp_pid);
			if (p == NULL)
				return (EINVAL);
			if (!P_SHOULDSTOP(p) ||
			    (p->p_flag & (P_TRACED | P_WEXIT)) != P_TRACED ||
			    p->p_pptr != curproc) {
				PROC_UNLOCK(p);
				return (EINVAL);
			}
			_PHOLD(p);
			PROC_UNLOCK(p);
			dof = dtrace_dof_copyin_proc(p, (uintptr_t)addr, &rval);
		}

		if (dof == NULL) {
			if (p != curproc)
				PRELE(p);
			break;
		}

		mutex_enter(&dtrace_lock);
		if ((rval = dtrace_helper_slurp(dof, dhp, p)) != -1) {
			dhp->dofhp_gen = rval;
			rval = 0;
		} else {
			rval = EINVAL;
		}
		mutex_exit(&dtrace_lock);
		if (p != curproc)
			PRELE(p);
		break;
	case DTRACEHIOC_REMOVE:
		mutex_enter(&dtrace_lock);
		rval = dtrace_helper_destroygen(NULL, *(int *)(uintptr_t)addr);
		mutex_exit(&dtrace_lock);
		break;
	default:
		rval = ENOTTY;
		break;
	}
	return (rval);
}