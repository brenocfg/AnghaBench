#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_quad_t ;
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {void* tv_nsec; void* tv_sec; } ;
struct nfsvattr {scalar_t__ na_type; int na_rdev; scalar_t__ na_size; int /*<<< orphan*/  na_vattr; TYPE_1__ na_atime; } ;
struct nfsrv_descript {int nd_repstat; int /*<<< orphan*/  nd_cred; } ;
struct nfsexstuff {int dummy; } ;
struct nameidata {struct vnode* ni_dvp; struct vnode* ni_vp; struct vnode* ni_startdir; int /*<<< orphan*/  ni_cnd; } ;
typedef  void* int32_t ;
typedef  int NFSDEV_T ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  NFSACCCHK_NOOVERRIDE ; 
 int /*<<< orphan*/  NFSACCCHK_VPISLOCKED ; 
 int NFSERR_NOTSUPP ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  NFSVNO_ATTRINIT (struct nfsvattr*) ; 
 int /*<<< orphan*/  PRIV_VFS_MKNOD_DEV ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 scalar_t__ VFIFO ; 
 scalar_t__ VNOVAL ; 
 int VOP_CREATE (struct vnode*,struct vnode**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VOP_MKNOD (struct vnode*,struct vnode**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VOP_SETATTR (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 scalar_t__ VSOCK ; 
 int /*<<< orphan*/  VWRITE ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  nfsrv_pnfscreate (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread*) ; 
 int nfsvno_accchk (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsexstuff*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsvno_relpathbuf (struct nameidata*) ; 
 int priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
nfsvno_createsub(struct nfsrv_descript *nd, struct nameidata *ndp,
    struct vnode **vpp, struct nfsvattr *nvap, int *exclusive_flagp,
    int32_t *cverf, NFSDEV_T rdev, struct nfsexstuff *exp)
{
	u_quad_t tempsize;
	int error;
	struct thread *p = curthread;

	error = nd->nd_repstat;
	if (!error && ndp->ni_vp == NULL) {
		if (nvap->na_type == VREG || nvap->na_type == VSOCK) {
			vrele(ndp->ni_startdir);
			error = VOP_CREATE(ndp->ni_dvp,
			    &ndp->ni_vp, &ndp->ni_cnd, &nvap->na_vattr);
			/* For a pNFS server, create the data file on a DS. */
			if (error == 0 && nvap->na_type == VREG) {
				/*
				 * Create a data file on a DS for a pNFS server.
				 * This function just returns if not
				 * running a pNFS DS or the creation fails.
				 */
				nfsrv_pnfscreate(ndp->ni_vp, &nvap->na_vattr,
				    nd->nd_cred, p);
			}
			vput(ndp->ni_dvp);
			nfsvno_relpathbuf(ndp);
			if (!error) {
				if (*exclusive_flagp) {
					*exclusive_flagp = 0;
					NFSVNO_ATTRINIT(nvap);
					nvap->na_atime.tv_sec = cverf[0];
					nvap->na_atime.tv_nsec = cverf[1];
					error = VOP_SETATTR(ndp->ni_vp,
					    &nvap->na_vattr, nd->nd_cred);
					if (error != 0) {
						vput(ndp->ni_vp);
						ndp->ni_vp = NULL;
						error = NFSERR_NOTSUPP;
					}
				}
			}
		/*
		 * NFS V2 Only. nfsrvd_mknod() does this for V3.
		 * (This implies, just get out on an error.)
		 */
		} else if (nvap->na_type == VCHR || nvap->na_type == VBLK ||
			nvap->na_type == VFIFO) {
			if (nvap->na_type == VCHR && rdev == 0xffffffff)
				nvap->na_type = VFIFO;
                        if (nvap->na_type != VFIFO &&
			    (error = priv_check_cred(nd->nd_cred, PRIV_VFS_MKNOD_DEV))) {
				vrele(ndp->ni_startdir);
				nfsvno_relpathbuf(ndp);
				vput(ndp->ni_dvp);
				goto out;
			}
			nvap->na_rdev = rdev;
			error = VOP_MKNOD(ndp->ni_dvp, &ndp->ni_vp,
			    &ndp->ni_cnd, &nvap->na_vattr);
			vput(ndp->ni_dvp);
			nfsvno_relpathbuf(ndp);
			vrele(ndp->ni_startdir);
			if (error)
				goto out;
		} else {
			vrele(ndp->ni_startdir);
			nfsvno_relpathbuf(ndp);
			vput(ndp->ni_dvp);
			error = ENXIO;
			goto out;
		}
		*vpp = ndp->ni_vp;
	} else {
		/*
		 * Handle cases where error is already set and/or
		 * the file exists.
		 * 1 - clean up the lookup
		 * 2 - iff !error and na_size set, truncate it
		 */
		vrele(ndp->ni_startdir);
		nfsvno_relpathbuf(ndp);
		*vpp = ndp->ni_vp;
		if (ndp->ni_dvp == *vpp)
			vrele(ndp->ni_dvp);
		else
			vput(ndp->ni_dvp);
		if (!error && nvap->na_size != VNOVAL) {
			error = nfsvno_accchk(*vpp, VWRITE,
			    nd->nd_cred, exp, p, NFSACCCHK_NOOVERRIDE,
			    NFSACCCHK_VPISLOCKED, NULL);
			if (!error) {
				tempsize = nvap->na_size;
				NFSVNO_ATTRINIT(nvap);
				nvap->na_size = tempsize;
				error = VOP_SETATTR(*vpp,
				    &nvap->na_vattr, nd->nd_cred);
			}
		}
		if (error)
			vput(*vpp);
	}

out:
	NFSEXITCODE(error);
	return (error);
}