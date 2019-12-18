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
struct vop_rmdir_args {struct componentname* a_cnp; struct vnode* a_dvp; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsnode {scalar_t__ n_attrstamp; int /*<<< orphan*/  n_flag; } ;
struct componentname {int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int /*<<< orphan*/  NMODIFIED ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_rmdir (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_rmdir(struct vop_rmdir_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode *dvp = ap->a_dvp;
	struct componentname *cnp = ap->a_cnp;
	struct nfsnode *dnp;
	struct nfsvattr dnfsva;
	int error, dattrflag;

	if (dvp == vp)
		return (EINVAL);
	error = nfsrpc_rmdir(dvp, cnp->cn_nameptr, cnp->cn_namelen,
	    cnp->cn_cred, cnp->cn_thread, &dnfsva, &dattrflag, NULL);
	dnp = VTONFS(dvp);
	NFSLOCKNODE(dnp);
	dnp->n_flag |= NMODIFIED;
	if (dattrflag != 0) {
		NFSUNLOCKNODE(dnp);
		(void) nfscl_loadattrcache(&dvp, &dnfsva, NULL, NULL, 0, 1);
	} else {
		dnp->n_attrstamp = 0;
		NFSUNLOCKNODE(dnp);
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(dvp);
	}

	cache_purge(dvp);
	cache_purge(vp);
	if (error && NFS_ISV4(dvp))
		error = nfscl_maperr(cnp->cn_thread, error, (uid_t)0,
		    (gid_t)0);
	/*
	 * Kludge: Map ENOENT => 0 assuming that you have a reply to a retry.
	 */
	if (error == ENOENT)
		error = 0;
	return (error);
}