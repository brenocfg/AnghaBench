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
struct thread {TYPE_1__* td_ucred; int /*<<< orphan*/  td_cpuset; struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct prison {int /*<<< orphan*/  pr_mtx; struct cpuset* pr_cpuset; } ;
struct cpuset {int dummy; } ;
typedef  int id_t ;
typedef  int cpuwhich_t ;
struct TYPE_2__ {int /*<<< orphan*/  cr_prison; } ;

/* Variables and functions */
#define  CPU_WHICH_CPUSET 133 
#define  CPU_WHICH_DOMAIN 132 
#define  CPU_WHICH_IRQ 131 
#define  CPU_WHICH_JAIL 130 
#define  CPU_WHICH_PID 129 
#define  CPU_WHICH_TID 128 
 int EINVAL ; 
 int ESRCH ; 
 struct thread* FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  allprison_lock ; 
 struct cpuset* cpuset_lookup (int,struct thread*) ; 
 int /*<<< orphan*/  cpuset_ref (struct cpuset*) ; 
 struct cpuset* cpuset_refbase (int /*<<< orphan*/ ) ; 
 struct proc* curproc ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int p_cansched (struct thread*,struct proc*) ; 
 struct proc* pfind (int) ; 
 struct prison* prison_find_child (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 struct thread* tdfind (int,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
cpuset_which(cpuwhich_t which, id_t id, struct proc **pp, struct thread **tdp,
    struct cpuset **setp)
{
	struct cpuset *set;
	struct thread *td;
	struct proc *p;
	int error;

	*pp = p = NULL;
	*tdp = td = NULL;
	*setp = set = NULL;
	switch (which) {
	case CPU_WHICH_PID:
		if (id == -1) {
			PROC_LOCK(curproc);
			p = curproc;
			break;
		}
		if ((p = pfind(id)) == NULL)
			return (ESRCH);
		break;
	case CPU_WHICH_TID:
		if (id == -1) {
			PROC_LOCK(curproc);
			p = curproc;
			td = curthread;
			break;
		}
		td = tdfind(id, -1);
		if (td == NULL)
			return (ESRCH);
		p = td->td_proc;
		break;
	case CPU_WHICH_CPUSET:
		if (id == -1) {
			thread_lock(curthread);
			set = cpuset_refbase(curthread->td_cpuset);
			thread_unlock(curthread);
		} else
			set = cpuset_lookup(id, curthread);
		if (set) {
			*setp = set;
			return (0);
		}
		return (ESRCH);
	case CPU_WHICH_JAIL:
	{
		/* Find `set' for prison with given id. */
		struct prison *pr;

		sx_slock(&allprison_lock);
		pr = prison_find_child(curthread->td_ucred->cr_prison, id);
		sx_sunlock(&allprison_lock);
		if (pr == NULL)
			return (ESRCH);
		cpuset_ref(pr->pr_cpuset);
		*setp = pr->pr_cpuset;
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	case CPU_WHICH_IRQ:
	case CPU_WHICH_DOMAIN:
		return (0);
	default:
		return (EINVAL);
	}
	error = p_cansched(curthread, p);
	if (error) {
		PROC_UNLOCK(p);
		return (error);
	}
	if (td == NULL)
		td = FIRST_THREAD_IN_PROC(p);
	*pp = p;
	*tdp = td;
	return (0);
}