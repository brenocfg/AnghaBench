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
struct vop_close_args {int a_fflag; int /*<<< orphan*/  a_td; struct ucred* a_cred; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; scalar_t__ v_object; } ;
struct ucred {int dummy; } ;
struct nfsvattr {int /*<<< orphan*/  na_filerev; } ;
struct nfsnode {int n_flag; int n_error; scalar_t__ n_directio_asyncwr; scalar_t__ n_directio_opens; int /*<<< orphan*/  n_change; scalar_t__ n_attrstamp; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {scalar_t__ nm_negnametimeo; int nm_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 scalar_t__ NFSCL_FORCEDISM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSFREECRED (struct ucred*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int NFSMNT_NOCTO ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV3 (struct vnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int NMODIFIED ; 
 int NNONCACHE ; 
 struct ucred* NOCRED ; 
 int NWRITEERR ; 
 int O_DIRECT ; 
 TYPE_1__* VFSTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (scalar_t__) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (scalar_t__) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int ncl_flush (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ncl_vinvalbuf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ newnfs_commit_on_close ; 
 scalar_t__ newnfs_directio_enable ; 
 struct ucred* newnfs_getcred () ; 
 scalar_t__ nfs_clean_pages_on_close ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfscl_maperr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfscl_mustflush (struct vnode*) ; 
 int nfsrpc_close (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_getattr (struct vnode*,struct ucred*,int /*<<< orphan*/ ,struct nfsvattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_page_clean (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_close(struct vop_close_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct nfsnode *np = VTONFS(vp);
	struct nfsvattr nfsva;
	struct ucred *cred;
	int error = 0, ret, localcred = 0;
	int fmode = ap->a_fflag;

	if (NFSCL_FORCEDISM(vp->v_mount))
		return (0);
	/*
	 * During shutdown, a_cred isn't valid, so just use root.
	 */
	if (ap->a_cred == NOCRED) {
		cred = newnfs_getcred();
		localcred = 1;
	} else {
		cred = ap->a_cred;
	}
	if (vp->v_type == VREG) {
	    /*
	     * Examine and clean dirty pages, regardless of NMODIFIED.
	     * This closes a major hole in close-to-open consistency.
	     * We want to push out all dirty pages (and buffers) on
	     * close, regardless of whether they were dirtied by
	     * mmap'ed writes or via write().
	     */
	    if (nfs_clean_pages_on_close && vp->v_object) {
		VM_OBJECT_WLOCK(vp->v_object);
		vm_object_page_clean(vp->v_object, 0, 0, 0);
		VM_OBJECT_WUNLOCK(vp->v_object);
	    }
	    NFSLOCKNODE(np);
	    if (np->n_flag & NMODIFIED) {
		NFSUNLOCKNODE(np);
		if (NFS_ISV3(vp)) {
		    /*
		     * Under NFSv3 we have dirty buffers to dispose of.  We
		     * must flush them to the NFS server.  We have the option
		     * of waiting all the way through the commit rpc or just
		     * waiting for the initial write.  The default is to only
		     * wait through the initial write so the data is in the
		     * server's cache, which is roughly similar to the state
		     * a standard disk subsystem leaves the file in on close().
		     *
		     * We cannot clear the NMODIFIED bit in np->n_flag due to
		     * potential races with other processes, and certainly
		     * cannot clear it if we don't commit.
		     * These races occur when there is no longer the old
		     * traditional vnode locking implemented for Vnode Ops.
		     */
		    int cm = newnfs_commit_on_close ? 1 : 0;
		    error = ncl_flush(vp, MNT_WAIT, ap->a_td, cm, 0);
		    /* np->n_flag &= ~NMODIFIED; */
		} else if (NFS_ISV4(vp)) { 
			if (nfscl_mustflush(vp) != 0) {
				int cm = newnfs_commit_on_close ? 1 : 0;
				error = ncl_flush(vp, MNT_WAIT, ap->a_td,
				    cm, 0);
				/*
				 * as above w.r.t races when clearing
				 * NMODIFIED.
				 * np->n_flag &= ~NMODIFIED;
				 */
			}
		} else {
			error = ncl_vinvalbuf(vp, V_SAVE, ap->a_td, 1);
		}
		NFSLOCKNODE(np);
	    }
 	    /* 
 	     * Invalidate the attribute cache in all cases.
 	     * An open is going to fetch fresh attrs any way, other procs
 	     * on this node that have file open will be forced to do an 
 	     * otw attr fetch, but this is safe.
	     * --> A user found that their RPC count dropped by 20% when
	     *     this was commented out and I can't see any requirement
	     *     for it, so I've disabled it when negative lookups are
	     *     enabled. (What does this have to do with negative lookup
	     *     caching? Well nothing, except it was reported by the
	     *     same user that needed negative lookup caching and I wanted
	     *     there to be a way to disable it to see if it
	     *     is the cause of some caching/coherency issue that might
	     *     crop up.)
 	     */
	    if (VFSTONFS(vp->v_mount)->nm_negnametimeo == 0) {
		    np->n_attrstamp = 0;
		    KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
	    }
	    if (np->n_flag & NWRITEERR) {
		np->n_flag &= ~NWRITEERR;
		error = np->n_error;
	    }
	    NFSUNLOCKNODE(np);
	}

	if (NFS_ISV4(vp)) {
		/*
		 * Get attributes so "change" is up to date.
		 */
		if (error == 0 && nfscl_mustflush(vp) != 0 &&
		    vp->v_type == VREG &&
		    (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NOCTO) == 0) {
			ret = nfsrpc_getattr(vp, cred, ap->a_td, &nfsva,
			    NULL);
			if (!ret) {
				np->n_change = nfsva.na_filerev;
				(void) nfscl_loadattrcache(&vp, &nfsva, NULL,
				    NULL, 0, 0);
			}
		}

		/*
		 * and do the close.
		 */
		ret = nfsrpc_close(vp, 0, ap->a_td);
		if (!error && ret)
			error = ret;
		if (error)
			error = nfscl_maperr(ap->a_td, error, (uid_t)0,
			    (gid_t)0);
	}
	if (newnfs_directio_enable)
		KASSERT((np->n_directio_asyncwr == 0),
			("nfs_close: dirty unflushed (%d) directio buffers\n",
			 np->n_directio_asyncwr));
	if (newnfs_directio_enable && (fmode & O_DIRECT) && (vp->v_type == VREG)) {
		NFSLOCKNODE(np);
		KASSERT((np->n_directio_opens > 0), 
			("nfs_close: unexpectedly value (0) of n_directio_opens\n"));
		np->n_directio_opens--;
		if (np->n_directio_opens == 0)
			np->n_flag &= ~NNONCACHE;
		NFSUNLOCKNODE(np);
	}
	if (localcred)
		NFSFREECRED(cred);
	return (error);
}