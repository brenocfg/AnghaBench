#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_cpuset; } ;
struct proc {int dummy; } ;
struct cpuset {int dummy; } ;
typedef  int id_t ;
typedef  scalar_t__ cpuwhich_t ;
struct TYPE_11__ {int /*<<< orphan*/  __bits; } ;
typedef  TYPE_1__ cpuset_t ;
typedef  int cpulevel_t ;

/* Variables and functions */
#define  CPU_LEVEL_CPUSET 138 
#define  CPU_LEVEL_ROOT 137 
#define  CPU_LEVEL_WHICH 136 
 size_t CPU_MAXSIZE ; 
#define  CPU_WHICH_CPUSET 135 
#define  CPU_WHICH_DOMAIN 134 
#define  CPU_WHICH_INTRHANDLER 133 
#define  CPU_WHICH_IRQ 132 
#define  CPU_WHICH_ITHREAD 131 
#define  CPU_WHICH_JAIL 130 
#define  CPU_WHICH_PID 129 
#define  CPU_WHICH_TID 128 
 int ECAPMODE ; 
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 size_t NBBY ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int copyin (TYPE_1__ const*,TYPE_1__*,size_t) ; 
 int cpuset_modify (struct cpuset*,TYPE_1__*) ; 
 struct cpuset* cpuset_ref (int /*<<< orphan*/ ) ; 
 struct cpuset* cpuset_refbase (struct cpuset*) ; 
 struct cpuset* cpuset_refroot (struct cpuset*) ; 
 int /*<<< orphan*/  cpuset_rel (struct cpuset*) ; 
 int cpuset_setproc (int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int cpuset_setthread (int,TYPE_1__*) ; 
 int cpuset_which (scalar_t__,int,struct proc**,struct thread**,struct cpuset**) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int intr_setaffinity (int,scalar_t__,TYPE_1__*) ; 
 TYPE_1__* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
kern_cpuset_setaffinity(struct thread *td, cpulevel_t level, cpuwhich_t which,
    id_t id, size_t cpusetsize, const cpuset_t *maskp)
{
	struct cpuset *nset;
	struct cpuset *set;
	struct thread *ttd;
	struct proc *p;
	cpuset_t *mask;
	int error;

	if (cpusetsize < sizeof(cpuset_t) || cpusetsize > CPU_MAXSIZE / NBBY)
		return (ERANGE);
	/* In Capability mode, you can only set your own CPU set. */
	if (IN_CAPABILITY_MODE(td)) {
		if (level != CPU_LEVEL_WHICH)
			return (ECAPMODE);
		if (which != CPU_WHICH_TID && which != CPU_WHICH_PID)
			return (ECAPMODE);
		if (id != -1)
			return (ECAPMODE);
	}
	mask = malloc(cpusetsize, M_TEMP, M_WAITOK | M_ZERO);
	error = copyin(maskp, mask, cpusetsize);
	if (error)
		goto out;
	/*
	 * Verify that no high bits are set.
	 */
	if (cpusetsize > sizeof(cpuset_t)) {
		char *end;
		char *cp;

		end = cp = (char *)&mask->__bits;
		end += cpusetsize;
		cp += sizeof(cpuset_t);
		while (cp != end)
			if (*cp++ != 0) {
				error = EINVAL;
				goto out;
			}

	}
	switch (level) {
	case CPU_LEVEL_ROOT:
	case CPU_LEVEL_CPUSET:
		error = cpuset_which(which, id, &p, &ttd, &set);
		if (error)
			break;
		switch (which) {
		case CPU_WHICH_TID:
		case CPU_WHICH_PID:
			thread_lock(ttd);
			set = cpuset_ref(ttd->td_cpuset);
			thread_unlock(ttd);
			PROC_UNLOCK(p);
			break;
		case CPU_WHICH_CPUSET:
		case CPU_WHICH_JAIL:
			break;
		case CPU_WHICH_IRQ:
		case CPU_WHICH_INTRHANDLER:
		case CPU_WHICH_ITHREAD:
		case CPU_WHICH_DOMAIN:
			error = EINVAL;
			goto out;
		}
		if (level == CPU_LEVEL_ROOT)
			nset = cpuset_refroot(set);
		else
			nset = cpuset_refbase(set);
		error = cpuset_modify(nset, mask);
		cpuset_rel(nset);
		cpuset_rel(set);
		break;
	case CPU_LEVEL_WHICH:
		switch (which) {
		case CPU_WHICH_TID:
			error = cpuset_setthread(id, mask);
			break;
		case CPU_WHICH_PID:
			error = cpuset_setproc(id, NULL, mask, NULL);
			break;
		case CPU_WHICH_CPUSET:
		case CPU_WHICH_JAIL:
			error = cpuset_which(which, id, &p, &ttd, &set);
			if (error == 0) {
				error = cpuset_modify(set, mask);
				cpuset_rel(set);
			}
			break;
		case CPU_WHICH_IRQ:
		case CPU_WHICH_INTRHANDLER:
		case CPU_WHICH_ITHREAD:
			error = intr_setaffinity(id, which, mask);
			break;
		default:
			error = EINVAL;
			break;
		}
		break;
	default:
		error = EINVAL;
		break;
	}
out:
	free(mask, M_TEMP);
	return (error);
}