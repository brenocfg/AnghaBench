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
typedef  int /*<<< orphan*/  uid_t ;
struct vop_link_args {struct componentname* a_cnp; struct vnode* a_tdvp; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct nfsvattr {int /*<<< orphan*/  na_ctime; } ;
struct nfsnode {scalar_t__ n_attrstamp; int /*<<< orphan*/  n_flag; } ;
struct componentname {int cn_flags; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {scalar_t__ nm_negnametimeo; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int MAKEENTRY ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int /*<<< orphan*/  NMODIFIED ; 
 TYPE_1__* VFSTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_FSYNC (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  cache_enter_time (struct vnode*,struct vnode*,struct componentname*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfscl_maperr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_link (struct vnode*,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsvattr*,struct nfsvattr*,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_link(struct vop_link_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode *tdvp = ap->a_tdvp;
	struct componentname *cnp = ap->a_cnp;
	struct nfsnode *np, *tdnp;
	struct nfsvattr nfsva, dnfsva;
	int error = 0, attrflag, dattrflag;

	/*
	 * Push all writes to the server, so that the attribute cache
	 * doesn't get "out of sync" with the server.
	 * XXX There should be a better way!
	 */
	VOP_FSYNC(vp, MNT_WAIT, cnp->cn_thread);

	error = nfsrpc_link(tdvp, vp, cnp->cn_nameptr, cnp->cn_namelen,
	    cnp->cn_cred, cnp->cn_thread, &dnfsva, &nfsva, &attrflag,
	    &dattrflag, NULL);
	tdnp = VTONFS(tdvp);
	NFSLOCKNODE(tdnp);
	tdnp->n_flag |= NMODIFIED;
	if (dattrflag != 0) {
		NFSUNLOCKNODE(tdnp);
		(void) nfscl_loadattrcache(&tdvp, &dnfsva, NULL, NULL, 0, 1);
	} else {
		tdnp->n_attrstamp = 0;
		NFSUNLOCKNODE(tdnp);
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(tdvp);
	}
	if (attrflag)
		(void) nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0, 1);
	else {
		np = VTONFS(vp);
		NFSLOCKNODE(np);
		np->n_attrstamp = 0;
		NFSUNLOCKNODE(np);
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
	}
	/*
	 * If negative lookup caching is enabled, I might as well
	 * add an entry for this node. Not necessary for correctness,
	 * but if negative caching is enabled, then the system
	 * must care about lookup caching hit rate, so...
	 */
	if (VFSTONFS(vp->v_mount)->nm_negnametimeo != 0 &&
	    (cnp->cn_flags & MAKEENTRY) && attrflag != 0 && error == 0) {
		cache_enter_time(tdvp, vp, cnp, &nfsva.na_ctime, NULL);
	}
	if (error && NFS_ISV4(vp))
		error = nfscl_maperr(cnp->cn_thread, error, (uid_t)0,
		    (gid_t)0);
	return (error);
}