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
struct ucred {int cr_ngroups; int /*<<< orphan*/ * cr_groups; } ;
struct thread {int* td_retval; struct ucred* td_ucred; } ;
struct linux_getgroups_args {int gidsetsize; int /*<<< orphan*/  grouplist; } ;
typedef  int /*<<< orphan*/  l_gid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_LINUX ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_getgroups(struct thread *td, struct linux_getgroups_args *args)
{
	struct ucred *cred;
	l_gid_t *linux_gidset;
	gid_t *bsd_gidset;
	int bsd_gidsetsz, ngrp, error;

	cred = td->td_ucred;
	bsd_gidset = cred->cr_groups;
	bsd_gidsetsz = cred->cr_ngroups - 1;

	/*
	 * cr_groups[0] holds egid. Returning the whole set
	 * here will cause a duplicate. Exclude cr_groups[0]
	 * to prevent that.
	 */

	if ((ngrp = args->gidsetsize) == 0) {
		td->td_retval[0] = bsd_gidsetsz;
		return (0);
	}

	if (ngrp < bsd_gidsetsz)
		return (EINVAL);

	ngrp = 0;
	linux_gidset = malloc(bsd_gidsetsz * sizeof(*linux_gidset),
	    M_LINUX, M_WAITOK);
	while (ngrp < bsd_gidsetsz) {
		linux_gidset[ngrp] = bsd_gidset[ngrp + 1];
		ngrp++;
	}

	error = copyout(linux_gidset, args->grouplist, ngrp * sizeof(l_gid_t));
	free(linux_gidset, M_LINUX);
	if (error)
		return (error);

	td->td_retval[0] = ngrp;
	return (0);
}