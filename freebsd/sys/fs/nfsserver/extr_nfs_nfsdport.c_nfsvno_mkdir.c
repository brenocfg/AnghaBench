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
struct nameidata {scalar_t__ ni_dvp; scalar_t__ ni_vp; int /*<<< orphan*/  ni_cnd; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int VOP_MKDIR (scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsvno_relpathbuf (struct nameidata*) ; 
 int /*<<< orphan*/  vput (scalar_t__) ; 
 int /*<<< orphan*/  vrele (scalar_t__) ; 

int
nfsvno_mkdir(struct nameidata *ndp, struct nfsvattr *nvap, uid_t saved_uid,
    struct ucred *cred, struct thread *p, struct nfsexstuff *exp)
{
	int error = 0;

	if (ndp->ni_vp != NULL) {
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
		else
			vput(ndp->ni_dvp);
		vrele(ndp->ni_vp);
		nfsvno_relpathbuf(ndp);
		error = EEXIST;
		goto out;
	}
	error = VOP_MKDIR(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd,
	    &nvap->na_vattr);
	vput(ndp->ni_dvp);
	nfsvno_relpathbuf(ndp);

out:
	NFSEXITCODE(error);
	return (error);
}