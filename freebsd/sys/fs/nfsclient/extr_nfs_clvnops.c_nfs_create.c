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
typedef  scalar_t__ uid_t ;
struct vop_create_args {struct vnode** a_vpp; struct componentname* a_cnp; struct vattr* a_vap; struct vnode* a_dvp; } ;
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct vattr {scalar_t__ va_type; int va_vaflags; scalar_t__ va_uid; scalar_t__ va_gid; } ;
struct nfsvattr {int /*<<< orphan*/  na_ctime; } ;
struct nfsnode {int n_flag; scalar_t__ n_attrstamp; int /*<<< orphan*/  n_mtx; } ;
struct nfsmount {int dummy; } ;
struct nfsfh {int dummy; } ;
struct componentname {int cn_flags; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  int /*<<< orphan*/  nfsquad_t ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int MAKEENTRY ; 
 int NFSERR_NOTSUPP ; 
 scalar_t__ NFSHASNFSV4 (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 struct vnode* NFSTOV (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV34 (struct vnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int NMODIFIED ; 
 int NREMOVEINPROG ; 
 int NREMOVEWANT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  PZERO ; 
 int VA_EXCLUSIVE ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 scalar_t__ VNOVAL ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VSOCK ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  cache_enter_time (struct vnode*,struct vnode*,struct componentname*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_get_cverf () ; 
 int nfs_mknodrpc (struct vnode*,struct vnode**,struct componentname*,struct vattr*) ; 
 scalar_t__ nfscl_checksattr (struct vattr*,struct nfsvattr*) ; 
 int nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int nfscl_nget (int /*<<< orphan*/ ,struct vnode*,struct nfsfh*,struct componentname*,int /*<<< orphan*/ ,struct nfsnode**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfsrpc_create (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vattr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsvattr*,struct nfsvattr*,struct nfsfh**,int*,int*,int /*<<< orphan*/ *) ; 
 int nfsrpc_getattr (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsvattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrpc_lookup (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsvattr*,struct nfsvattr*,struct nfsfh**,int*,int*,int /*<<< orphan*/ *) ; 
 int nfsrpc_setattr (struct vnode*,struct vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
nfs_create(struct vop_create_args *ap)
{
	struct vnode *dvp = ap->a_dvp;
	struct vattr *vap = ap->a_vap;
	struct componentname *cnp = ap->a_cnp;
	struct nfsnode *np = NULL, *dnp;
	struct vnode *newvp = NULL;
	struct nfsmount *nmp;
	struct nfsvattr dnfsva, nfsva;
	struct nfsfh *nfhp;
	nfsquad_t cverf;
	int error = 0, attrflag, dattrflag, fmode = 0;
	struct vattr vattr;

	/*
	 * Oops, not for me..
	 */
	if (vap->va_type == VSOCK)
		return (nfs_mknodrpc(dvp, ap->a_vpp, cnp, vap));

	if ((error = VOP_GETATTR(dvp, &vattr, cnp->cn_cred)))
		return (error);
	if (vap->va_vaflags & VA_EXCLUSIVE)
		fmode |= O_EXCL;
	dnp = VTONFS(dvp);
	nmp = VFSTONFS(vnode_mount(dvp));
again:
	/* For NFSv4, wait until any remove is done. */
	NFSLOCKNODE(dnp);
	while (NFSHASNFSV4(nmp) && (dnp->n_flag & NREMOVEINPROG)) {
		dnp->n_flag |= NREMOVEWANT;
		(void) msleep((caddr_t)dnp, &dnp->n_mtx, PZERO, "nfscrt", 0);
	}
	NFSUNLOCKNODE(dnp);

	cverf = nfs_get_cverf();
	error = nfsrpc_create(dvp, cnp->cn_nameptr, cnp->cn_namelen,
	    vap, cverf, fmode, cnp->cn_cred, cnp->cn_thread, &dnfsva, &nfsva,
	    &nfhp, &attrflag, &dattrflag, NULL);
	if (!error) {
		if (nfhp == NULL)
			(void) nfsrpc_lookup(dvp, cnp->cn_nameptr,
			    cnp->cn_namelen, cnp->cn_cred, cnp->cn_thread,
			    &dnfsva, &nfsva, &nfhp, &attrflag, &dattrflag,
			    NULL);
		if (nfhp != NULL)
			error = nfscl_nget(dvp->v_mount, dvp, nfhp, cnp,
			    cnp->cn_thread, &np, NULL, LK_EXCLUSIVE);
	}
	if (dattrflag)
		(void) nfscl_loadattrcache(&dvp, &dnfsva, NULL, NULL, 0, 1);
	if (!error) {
		newvp = NFSTOV(np);
		if (attrflag == 0)
			error = nfsrpc_getattr(newvp, cnp->cn_cred,
			    cnp->cn_thread, &nfsva, NULL);
		if (error == 0)
			error = nfscl_loadattrcache(&newvp, &nfsva, NULL, NULL,
			    0, 1);
	}
	if (error) {
		if (newvp != NULL) {
			vput(newvp);
			newvp = NULL;
		}
		if (NFS_ISV34(dvp) && (fmode & O_EXCL) &&
		    error == NFSERR_NOTSUPP) {
			fmode &= ~O_EXCL;
			goto again;
		}
	} else if (NFS_ISV34(dvp) && (fmode & O_EXCL)) {
		if (nfscl_checksattr(vap, &nfsva)) {
			error = nfsrpc_setattr(newvp, vap, NULL, cnp->cn_cred,
			    cnp->cn_thread, &nfsva, &attrflag, NULL);
			if (error && (vap->va_uid != (uid_t)VNOVAL ||
			    vap->va_gid != (gid_t)VNOVAL)) {
				/* try again without setting uid/gid */
				vap->va_uid = (uid_t)VNOVAL;
				vap->va_gid = (uid_t)VNOVAL;
				error = nfsrpc_setattr(newvp, vap, NULL, 
				    cnp->cn_cred, cnp->cn_thread, &nfsva,
				    &attrflag, NULL);
			}
			if (attrflag)
				(void) nfscl_loadattrcache(&newvp, &nfsva, NULL,
				    NULL, 0, 1);
			if (error != 0)
				vput(newvp);
		}
	}
	if (!error) {
		if ((cnp->cn_flags & MAKEENTRY) && attrflag)
			cache_enter_time(dvp, newvp, cnp, &nfsva.na_ctime,
			    NULL);
		*ap->a_vpp = newvp;
	} else if (NFS_ISV4(dvp)) {
		error = nfscl_maperr(cnp->cn_thread, error, vap->va_uid,
		    vap->va_gid);
	}
	NFSLOCKNODE(dnp);
	dnp->n_flag |= NMODIFIED;
	if (!dattrflag) {
		dnp->n_attrstamp = 0;
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(dvp);
	}
	NFSUNLOCKNODE(dnp);
	return (error);
}