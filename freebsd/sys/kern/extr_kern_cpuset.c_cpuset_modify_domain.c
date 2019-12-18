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
struct domainset {scalar_t__ ds_policy; int /*<<< orphan*/  ds_mask; } ;
struct domainlist {int dummy; } ;
struct cpuset {int cs_flags; struct domainset* cs_domain; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int CPU_SET_ROOT ; 
 int /*<<< orphan*/  DOMAINSET_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_POLICY_PREFER ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  PRIV_SCHED_CPUSET ; 
 struct cpuset* cpuset_getroot (struct cpuset*) ; 
 int /*<<< orphan*/  cpuset_lock ; 
 int cpuset_testupdate_domain (struct cpuset*,struct domainset*,struct domainset*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_update_domain (struct cpuset*,struct domainset*,struct domainset*,struct domainlist*) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  domainset_copy (struct domainset*,struct domainset*) ; 
 struct domainset* domainset_create (struct domainset*) ; 
 int /*<<< orphan*/  domainset_freelist_add (struct domainlist*,int) ; 
 int /*<<< orphan*/  domainset_freelist_free (struct domainlist*) ; 
 int /*<<< orphan*/  domainset_freelist_init (struct domainlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domainset_notify () ; 
 int /*<<< orphan*/  domainset_valid (struct domainset*,struct domainset*) ; 
 scalar_t__ jailed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int priv_check (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpuset_modify_domain(struct cpuset *set, struct domainset *domain)
{
	struct domainlist domains;
	struct domainset temp;
	struct domainset *dset;
	struct cpuset *root;
	int ndomains, needed;
	int error;

	error = priv_check(curthread, PRIV_SCHED_CPUSET);
	if (error)
		return (error);
	/*
	 * In case we are called from within the jail
	 * we do not allow modifying the dedicated root
	 * cpuset of the jail but may still allow to
	 * change child sets.
	 */
	if (jailed(curthread->td_ucred) &&
	    set->cs_flags & CPU_SET_ROOT)
		return (EPERM);
	domainset_freelist_init(&domains, 0);
	domain = domainset_create(domain);
	ndomains = needed = 0;
	do {
		if (ndomains < needed) {
			domainset_freelist_add(&domains, needed - ndomains);
			ndomains = needed;
		}
		root = cpuset_getroot(set);
		mtx_lock_spin(&cpuset_lock);
		dset = root->cs_domain;
		/*
		 * Verify that we have access to this set of domains.
		 */
		if (!domainset_valid(dset, domain)) {
			error = EINVAL;
			goto out;
		}
		/*
		 * If applying prefer we keep the current set as the fallback.
		 */
		if (domain->ds_policy == DOMAINSET_POLICY_PREFER)
			DOMAINSET_COPY(&set->cs_domain->ds_mask,
			    &domain->ds_mask);
		/*
		 * Determine whether we can apply this set of domains and
		 * how many new domain structures it will require.
		 */
		domainset_copy(domain, &temp);
		needed = 0;
		error = cpuset_testupdate_domain(set, &temp, set->cs_domain,
		    &needed, 0);
		if (error)
			goto out;
	} while (ndomains < needed);
	dset = set->cs_domain;
	cpuset_update_domain(set, domain, dset, &domains);
out:
	mtx_unlock_spin(&cpuset_lock);
	domainset_freelist_free(&domains);
	if (error == 0)
		domainset_notify();

	return (error);
}