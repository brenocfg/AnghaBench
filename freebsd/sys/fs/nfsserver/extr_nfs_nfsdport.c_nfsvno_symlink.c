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
typedef  int /*<<< orphan*/  uid_t ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {int /*<<< orphan*/  na_vattr; } ;
struct nfsexstuff {int dummy; } ;
struct nameidata {scalar_t__ ni_vp; scalar_t__ ni_startdir; scalar_t__ ni_dvp; int /*<<< orphan*/  ni_cnd; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int VOP_SYMLINK (scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nfsvno_relpathbuf (struct nameidata*) ; 
 int /*<<< orphan*/  vput (scalar_t__) ; 
 int /*<<< orphan*/  vrele (scalar_t__) ; 

int
nfsvno_symlink(struct nameidata *ndp, struct nfsvattr *nvap, char *pathcp,
    int pathlen, int not_v2, uid_t saved_uid, struct ucred *cred, struct thread *p,
    struct nfsexstuff *exp)
{
	int error = 0;

	if (ndp->ni_vp) {
		vrele(ndp->ni_startdir);
		nfsvno_relpathbuf(ndp);
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
		else
			vput(ndp->ni_dvp);
		vrele(ndp->ni_vp);
		error = EEXIST;
		goto out;
	}

	error = VOP_SYMLINK(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd,
	    &nvap->na_vattr, pathcp);
	vput(ndp->ni_dvp);
	vrele(ndp->ni_startdir);
	nfsvno_relpathbuf(ndp);
	/*
	 * Although FreeBSD still had the lookup code in
	 * it for 7/current, there doesn't seem to be any
	 * point, since VOP_SYMLINK() returns the ni_vp.
	 * Just vput it for v2.
	 */
	if (!not_v2 && !error)
		vput(ndp->ni_vp);

out:
	NFSEXITCODE(error);
	return (error);
}