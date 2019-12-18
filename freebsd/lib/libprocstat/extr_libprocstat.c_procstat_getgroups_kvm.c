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
typedef  int /*<<< orphan*/  ucred ;
struct ucred {scalar_t__ p_ucred; int cr_ngroups; scalar_t__ cr_groups; } ;
struct proc {scalar_t__ p_ucred; int cr_ngroups; scalar_t__ cr_groups; } ;
struct kinfo_proc {scalar_t__ ki_paddr; int /*<<< orphan*/  ki_pid; } ;
typedef  int /*<<< orphan*/  proc ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  struct ucred gid_t ;

/* Variables and functions */
 scalar_t__ NOCRED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ucred*) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct ucred*,size_t) ; 
 struct ucred* malloc (size_t) ; 
 int /*<<< orphan*/  warn (char*,size_t) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gid_t *
procstat_getgroups_kvm(kvm_t *kd, struct kinfo_proc *kp, unsigned int *cntp)
{
	struct proc proc;
	struct ucred ucred;
	gid_t *groups;
	size_t len;

	assert(kd != NULL);
	assert(kp != NULL);
	if (!kvm_read_all(kd, (unsigned long)kp->ki_paddr, &proc,
	    sizeof(proc))) {
		warnx("can't read proc struct at %p for pid %d",
		    kp->ki_paddr, kp->ki_pid);
		return (NULL);
	}
	if (proc.p_ucred == NOCRED)
		return (NULL);
	if (!kvm_read_all(kd, (unsigned long)proc.p_ucred, &ucred,
	    sizeof(ucred))) {
		warnx("can't read ucred struct at %p for pid %d",
		    proc.p_ucred, kp->ki_pid);
		return (NULL);
	}
	len = ucred.cr_ngroups * sizeof(gid_t);
	groups = malloc(len);
	if (groups == NULL) {
		warn("malloc(%zu)", len);
		return (NULL);
	}
	if (!kvm_read_all(kd, (unsigned long)ucred.cr_groups, groups, len)) {
		warnx("can't read groups at %p for pid %d",
		    ucred.cr_groups, kp->ki_pid);
		free(groups);
		return (NULL);
	}
	*cntp = ucred.cr_ngroups;
	return (groups);
}