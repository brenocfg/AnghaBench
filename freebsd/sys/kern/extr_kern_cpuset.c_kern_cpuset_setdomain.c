#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_cpuset; } ;
struct proc {int dummy; } ;
struct domainset {int ds_policy; int /*<<< orphan*/  ds_mask; scalar_t__ ds_prefer; } ;
struct cpuset {int dummy; } ;
typedef  int id_t ;
struct TYPE_10__ {int /*<<< orphan*/  __bits; } ;
typedef  TYPE_1__ domainset_t ;
typedef  int /*<<< orphan*/  domain ;
typedef  scalar_t__ cpuwhich_t ;
typedef  int cpulevel_t ;

/* Variables and functions */
#define  CPU_LEVEL_CPUSET 138 
#define  CPU_LEVEL_ROOT 137 
#define  CPU_LEVEL_WHICH 136 
#define  CPU_WHICH_CPUSET 135 
#define  CPU_WHICH_DOMAIN 134 
#define  CPU_WHICH_INTRHANDLER 133 
#define  CPU_WHICH_IRQ 132 
#define  CPU_WHICH_ITHREAD 131 
#define  CPU_WHICH_JAIL 130 
#define  CPU_WHICH_PID 129 
#define  CPU_WHICH_TID 128 
 int /*<<< orphan*/  DOMAINSET_COPY (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int DOMAINSET_COUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_FFS (int /*<<< orphan*/ *) ; 
 size_t DOMAINSET_MAXSIZE ; 
 int DOMAINSET_POLICY_INVALID ; 
 int DOMAINSET_POLICY_MAX ; 
 int DOMAINSET_POLICY_PREFER ; 
 int /*<<< orphan*/  DOMAINSET_SUBSET (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int ECAPMODE ; 
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 size_t NBBY ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int _cpuset_setthread (int,int /*<<< orphan*/ *,struct domainset*) ; 
 TYPE_1__ all_domains ; 
 int copyin (TYPE_1__ const*,TYPE_1__*,size_t) ; 
 int cpuset_modify_domain (struct cpuset*,struct domainset*) ; 
 struct cpuset* cpuset_ref (int /*<<< orphan*/ ) ; 
 struct cpuset* cpuset_refbase (struct cpuset*) ; 
 struct cpuset* cpuset_refroot (struct cpuset*) ; 
 int /*<<< orphan*/  cpuset_rel (struct cpuset*) ; 
 int cpuset_setproc (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct domainset*) ; 
 int cpuset_which (scalar_t__,int,struct proc**,struct thread**,struct cpuset**) ; 
 int /*<<< orphan*/  domainset2 ; 
 int /*<<< orphan*/  domainset_copy (int /*<<< orphan*/ *,struct domainset*) ; 
 scalar_t__ domainset_empty_vm (struct domainset*) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct domainset*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
kern_cpuset_setdomain(struct thread *td, cpulevel_t level, cpuwhich_t which,
    id_t id, size_t domainsetsize, const domainset_t *maskp, int policy)
{
	struct cpuset *nset;
	struct cpuset *set;
	struct thread *ttd;
	struct proc *p;
	struct domainset domain;
	domainset_t *mask;
	int error;

	if (domainsetsize < sizeof(domainset_t) ||
	    domainsetsize > DOMAINSET_MAXSIZE / NBBY)
		return (ERANGE);
	if (policy <= DOMAINSET_POLICY_INVALID ||
	    policy > DOMAINSET_POLICY_MAX)
		return (EINVAL);
	/* In Capability mode, you can only set your own CPU set. */
	if (IN_CAPABILITY_MODE(td)) {
		if (level != CPU_LEVEL_WHICH)
			return (ECAPMODE);
		if (which != CPU_WHICH_TID && which != CPU_WHICH_PID)
			return (ECAPMODE);
		if (id != -1)
			return (ECAPMODE);
	}
	memset(&domain, 0, sizeof(domain));
	mask = malloc(domainsetsize, M_TEMP, M_WAITOK | M_ZERO);
	error = copyin(maskp, mask, domainsetsize);
	if (error)
		goto out;
	/*
	 * Verify that no high bits are set.
	 */
	if (domainsetsize > sizeof(domainset_t)) {
		char *end;
		char *cp;

		end = cp = (char *)&mask->__bits;
		end += domainsetsize;
		cp += sizeof(domainset_t);
		while (cp != end)
			if (*cp++ != 0) {
				error = EINVAL;
				goto out;
			}

	}
	DOMAINSET_COPY(mask, &domain.ds_mask);
	domain.ds_policy = policy;

	/*
	 * Sanitize the provided mask.
	 */
	if (!DOMAINSET_SUBSET(&all_domains, &domain.ds_mask)) {
		error = EINVAL;
		goto out;
	}

	/* Translate preferred policy into a mask and fallback. */
	if (policy == DOMAINSET_POLICY_PREFER) {
		/* Only support a single preferred domain. */
		if (DOMAINSET_COUNT(&domain.ds_mask) != 1) {
			error = EINVAL;
			goto out;
		}
		domain.ds_prefer = DOMAINSET_FFS(&domain.ds_mask) - 1;
		/* This will be constrained by domainset_shadow(). */
		DOMAINSET_COPY(&all_domains, &domain.ds_mask);
	}

	/*
	 * When given an impossible policy, fall back to interleaving
	 * across all domains.
	 */
	if (domainset_empty_vm(&domain))
		domainset_copy(&domainset2, &domain);

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
		error = cpuset_modify_domain(nset, &domain);
		cpuset_rel(nset);
		cpuset_rel(set);
		break;
	case CPU_LEVEL_WHICH:
		switch (which) {
		case CPU_WHICH_TID:
			error = _cpuset_setthread(id, NULL, &domain);
			break;
		case CPU_WHICH_PID:
			error = cpuset_setproc(id, NULL, NULL, &domain);
			break;
		case CPU_WHICH_CPUSET:
		case CPU_WHICH_JAIL:
			error = cpuset_which(which, id, &p, &ttd, &set);
			if (error == 0) {
				error = cpuset_modify_domain(set, &domain);
				cpuset_rel(set);
			}
			break;
		case CPU_WHICH_IRQ:
		case CPU_WHICH_INTRHANDLER:
		case CPU_WHICH_ITHREAD:
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