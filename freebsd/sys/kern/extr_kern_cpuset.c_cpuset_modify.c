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
struct cpuset {int cs_flags; int /*<<< orphan*/  cs_mask; } ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CPU_SET_ROOT ; 
 int /*<<< orphan*/  CPU_SUBSET (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  PRIV_SCHED_CPUSET ; 
 struct cpuset* cpuset_getroot (struct cpuset*) ; 
 int /*<<< orphan*/  cpuset_lock ; 
 int cpuset_testupdate (struct cpuset*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_update (struct cpuset*,int /*<<< orphan*/ *) ; 
 TYPE_1__* curthread ; 
 scalar_t__ jailed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int priv_check (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpuset_modify(struct cpuset *set, cpuset_t *mask)
{
	struct cpuset *root;
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
	/*
	 * Verify that we have access to this set of
	 * cpus.
	 */
	root = cpuset_getroot(set);
	mtx_lock_spin(&cpuset_lock);
	if (root && !CPU_SUBSET(&root->cs_mask, mask)) {
		error = EINVAL;
		goto out;
	}
	error = cpuset_testupdate(set, mask, 0);
	if (error)
		goto out;
	CPU_COPY(mask, &set->cs_mask);
	cpuset_update(set, mask);
out:
	mtx_unlock_spin(&cpuset_lock);

	return (error);
}