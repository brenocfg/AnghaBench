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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsvattr {int na_type; int /*<<< orphan*/  na_vattr; } ;
struct nameidata {scalar_t__ ni_startdir; int /*<<< orphan*/  ni_dvp; int /*<<< orphan*/  ni_cnd; scalar_t__ ni_vp; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int EEXIST ; 
 int NFSERR_BADTYPE ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  PRIV_VFS_MKNOD_DEV ; 
 int VBLK ; 
 int VCHR ; 
 int VFIFO ; 
 int VOP_CREATE (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VOP_MKNOD (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VSOCK ; 
 int /*<<< orphan*/  nfsvno_relpathbuf (struct nameidata*) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (scalar_t__) ; 

int
nfsvno_mknod(struct nameidata *ndp, struct nfsvattr *nvap, struct ucred *cred,
    struct thread *p)
{
	int error = 0;
	enum vtype vtyp;

	vtyp = nvap->na_type;
	/*
	 * Iff doesn't exist, create it.
	 */
	if (ndp->ni_vp) {
		vrele(ndp->ni_startdir);
		nfsvno_relpathbuf(ndp);
		vput(ndp->ni_dvp);
		vrele(ndp->ni_vp);
		error = EEXIST;
		goto out;
	}
	if (vtyp != VCHR && vtyp != VBLK && vtyp != VSOCK && vtyp != VFIFO) {
		vrele(ndp->ni_startdir);
		nfsvno_relpathbuf(ndp);
		vput(ndp->ni_dvp);
		error = NFSERR_BADTYPE;
		goto out;
	}
	if (vtyp == VSOCK) {
		vrele(ndp->ni_startdir);
		error = VOP_CREATE(ndp->ni_dvp, &ndp->ni_vp,
		    &ndp->ni_cnd, &nvap->na_vattr);
		vput(ndp->ni_dvp);
		nfsvno_relpathbuf(ndp);
	} else {
		if (nvap->na_type != VFIFO &&
		    (error = priv_check_cred(cred, PRIV_VFS_MKNOD_DEV))) {
			vrele(ndp->ni_startdir);
			nfsvno_relpathbuf(ndp);
			vput(ndp->ni_dvp);
			goto out;
		}
		error = VOP_MKNOD(ndp->ni_dvp, &ndp->ni_vp,
		    &ndp->ni_cnd, &nvap->na_vattr);
		vput(ndp->ni_dvp);
		nfsvno_relpathbuf(ndp);
		vrele(ndp->ni_startdir);
		/*
		 * Since VOP_MKNOD returns the ni_vp, I can't
		 * see any reason to do the lookup.
		 */
	}

out:
	NFSEXITCODE(error);
	return (error);
}