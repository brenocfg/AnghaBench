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
struct vop_remove_args {struct componentname* a_cnp; struct vnode* a_dvp; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; } ;
struct vattr {int va_nlink; } ;
struct nfsnode {scalar_t__ n_attrstamp; scalar_t__ n_sillyrename; } ;
struct componentname {int cn_flags; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int ENOENT ; 
 int EPERM ; 
 int HASBUF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ VDIR ; 
 scalar_t__ VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int ncl_vinvalbuf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nfs_removerpc (struct vnode*,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_sillyrename (struct vnode*,struct vnode*,struct componentname*) ; 
 int vrefcnt (struct vnode*) ; 

__attribute__((used)) static int
nfs_remove(struct vop_remove_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode *dvp = ap->a_dvp;
	struct componentname *cnp = ap->a_cnp;
	struct nfsnode *np = VTONFS(vp);
	int error = 0;
	struct vattr vattr;

	KASSERT((cnp->cn_flags & HASBUF) != 0, ("nfs_remove: no name"));
	KASSERT(vrefcnt(vp) > 0, ("nfs_remove: bad v_usecount"));
	if (vp->v_type == VDIR)
		error = EPERM;
	else if (vrefcnt(vp) == 1 || (np->n_sillyrename &&
	    VOP_GETATTR(vp, &vattr, cnp->cn_cred) == 0 &&
	    vattr.va_nlink > 1)) {
		/*
		 * Purge the name cache so that the chance of a lookup for
		 * the name succeeding while the remove is in progress is
		 * minimized. Without node locking it can still happen, such
		 * that an I/O op returns ESTALE, but since you get this if
		 * another host removes the file..
		 */
		cache_purge(vp);
		/*
		 * throw away biocache buffers, mainly to avoid
		 * unnecessary delayed writes later.
		 */
		error = ncl_vinvalbuf(vp, 0, cnp->cn_thread, 1);
		if (error != EINTR && error != EIO)
			/* Do the rpc */
			error = nfs_removerpc(dvp, vp, cnp->cn_nameptr,
			    cnp->cn_namelen, cnp->cn_cred, cnp->cn_thread);
		/*
		 * Kludge City: If the first reply to the remove rpc is lost..
		 *   the reply to the retransmitted request will be ENOENT
		 *   since the file was in fact removed
		 *   Therefore, we cheat and return success.
		 */
		if (error == ENOENT)
			error = 0;
	} else if (!np->n_sillyrename)
		error = nfs_sillyrename(dvp, vp, cnp);
	NFSLOCKNODE(np);
	np->n_attrstamp = 0;
	NFSUNLOCKNODE(np);
	KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
	return (error);
}