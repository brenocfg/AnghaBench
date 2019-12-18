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
typedef  int u_int ;
struct ucred {int cr_ngroups; int /*<<< orphan*/  cr_groups; } ;
struct thread {int* td_retval; struct ucred* td_ucred; } ;
struct getgroups_args {scalar_t__ gidsetsize; int /*<<< orphan*/  gidset; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EINVAL ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
sys_getgroups(struct thread *td, struct getgroups_args *uap)
{
	struct ucred *cred;
	u_int ngrp;
	int error;

	cred = td->td_ucred;
	ngrp = cred->cr_ngroups;

	if (uap->gidsetsize == 0) {
		error = 0;
		goto out;
	}
	if (uap->gidsetsize < ngrp)
		return (EINVAL);

	error = copyout(cred->cr_groups, uap->gidset, ngrp * sizeof(gid_t));
out:
	td->td_retval[0] = ngrp;
	return (error);
}