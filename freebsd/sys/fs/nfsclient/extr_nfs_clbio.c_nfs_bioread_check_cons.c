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
struct vnode {scalar_t__ v_type; } ;
struct vattr {int /*<<< orphan*/  va_mtime; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsnode {int n_flag; int /*<<< orphan*/  n_mtime; scalar_t__ n_attrstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_TIMESPEC_COMPARE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NMODIFIED ; 
 int NSIZECHANGED ; 
 scalar_t__ VDIR ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int V_ALLOWCLEAN ; 
 int V_SAVE ; 
 int /*<<< orphan*/  ncl_excl_finish (struct vnode*,int) ; 
 int ncl_excl_start (struct vnode*) ; 
 int /*<<< orphan*/  ncl_invaldir (struct vnode*) ; 
 int ncl_vinvalbuf (struct vnode*,int,struct thread*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline int
nfs_bioread_check_cons(struct vnode *vp, struct thread *td, struct ucred *cred)
{
	int error = 0;
	struct vattr vattr;
	struct nfsnode *np = VTONFS(vp);
	bool old_lock;

	/*
	 * Ensure the exclusove access to the node before checking
	 * whether the cache is consistent.
	 */
	old_lock = ncl_excl_start(vp);
	NFSLOCKNODE(np);
	if (np->n_flag & NMODIFIED) {
		NFSUNLOCKNODE(np);
		if (vp->v_type != VREG) {
			if (vp->v_type != VDIR)
				panic("nfs: bioread, not dir");
			ncl_invaldir(vp);
			error = ncl_vinvalbuf(vp, V_SAVE | V_ALLOWCLEAN, td, 1);
			if (error != 0)
				goto out;
		}
		np->n_attrstamp = 0;
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
		error = VOP_GETATTR(vp, &vattr, cred);
		if (error)
			goto out;
		NFSLOCKNODE(np);
		np->n_mtime = vattr.va_mtime;
		NFSUNLOCKNODE(np);
	} else {
		NFSUNLOCKNODE(np);
		error = VOP_GETATTR(vp, &vattr, cred);
		if (error)
			goto out;
		NFSLOCKNODE(np);
		if ((np->n_flag & NSIZECHANGED)
		    || (NFS_TIMESPEC_COMPARE(&np->n_mtime, &vattr.va_mtime))) {
			NFSUNLOCKNODE(np);
			if (vp->v_type == VDIR)
				ncl_invaldir(vp);
			error = ncl_vinvalbuf(vp, V_SAVE | V_ALLOWCLEAN, td, 1);
			if (error != 0)
				goto out;
			NFSLOCKNODE(np);
			np->n_mtime = vattr.va_mtime;
			np->n_flag &= ~NSIZECHANGED;
		}
		NFSUNLOCKNODE(np);
	}
out:
	ncl_excl_finish(vp, old_lock);
	return (error);
}