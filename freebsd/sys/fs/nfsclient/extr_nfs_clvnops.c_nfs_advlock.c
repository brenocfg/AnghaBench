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
typedef  int /*<<< orphan*/  u_quad_t ;
struct vop_advlock_args {int a_flags; int /*<<< orphan*/  a_op; scalar_t__ a_id; int /*<<< orphan*/  a_fl; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int v_iflag; int /*<<< orphan*/  v_lockf; int /*<<< orphan*/  v_mount; } ;
struct vattr {scalar_t__ va_filerev; int /*<<< orphan*/  va_mtime; } ;
struct ucred {int dummy; } ;
struct thread {struct ucred* td_ucred; } ;
struct proc {struct ucred* p_ucred; } ;
struct nfsnode {int n_flag; scalar_t__ n_change; int /*<<< orphan*/  n_size; int /*<<< orphan*/  n_mtime; scalar_t__ n_attrstamp; } ;
struct TYPE_2__ {int nm_flag; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EBADF ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOLCK ; 
 int EOPNOTSUPP ; 
 int F_FLOCK ; 
 int F_POSIX ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int F_WAIT ; 
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int LK_UPGRADE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int NFSERR_DENIED ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int NFSMNT_NOLOCKD ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NFSVOPLOCK (struct vnode*,int) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int NHASBEENLOCKED ; 
 int NMODIFIED ; 
 int PCATCH ; 
 int PZERO ; 
 TYPE_1__* VFSTONFS (int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  V_SAVE ; 
 struct thread* curthread ; 
 int lf_advlock (struct vop_advlock_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncl_flush (struct vnode*,int /*<<< orphan*/ ,struct thread*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncl_vinvalbuf (struct vnode*,int /*<<< orphan*/ ,struct thread*,int) ; 
 int nfs_advlock_p (struct vop_advlock_args*) ; 
 int nfs_catnap (int,int,char*) ; 
 scalar_t__ nfscl_checkwritelocked (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*,scalar_t__,int) ; 
 int nfsrpc_advlock (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,struct thread*,scalar_t__,int) ; 

__attribute__((used)) static int
nfs_advlock(struct vop_advlock_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct ucred *cred;
	struct nfsnode *np = VTONFS(ap->a_vp);
	struct proc *p = (struct proc *)ap->a_id;
	struct thread *td = curthread;	/* XXX */
	struct vattr va;
	int ret, error;
	u_quad_t size;
	
	error = NFSVOPLOCK(vp, LK_SHARED);
	if (error != 0)
		return (EBADF);
	if (NFS_ISV4(vp) && (ap->a_flags & (F_POSIX | F_FLOCK)) != 0) {
		if (vp->v_type != VREG) {
			error = EINVAL;
			goto out;
		}
		if ((ap->a_flags & F_POSIX) != 0)
			cred = p->p_ucred;
		else
			cred = td->td_ucred;
		NFSVOPLOCK(vp, LK_UPGRADE | LK_RETRY);
		if (vp->v_iflag & VI_DOOMED) {
			error = EBADF;
			goto out;
		}

		/*
		 * If this is unlocking a write locked region, flush and
		 * commit them before unlocking. This is required by
		 * RFC3530 Sec. 9.3.2.
		 */
		if (ap->a_op == F_UNLCK &&
		    nfscl_checkwritelocked(vp, ap->a_fl, cred, td, ap->a_id,
		    ap->a_flags))
			(void) ncl_flush(vp, MNT_WAIT, td, 1, 0);

		/*
		 * Loop around doing the lock op, while a blocking lock
		 * must wait for the lock op to succeed.
		 */
		do {
			ret = nfsrpc_advlock(vp, np->n_size, ap->a_op,
			    ap->a_fl, 0, cred, td, ap->a_id, ap->a_flags);
			if (ret == NFSERR_DENIED && (ap->a_flags & F_WAIT) &&
			    ap->a_op == F_SETLK) {
				NFSVOPUNLOCK(vp, 0);
				error = nfs_catnap(PZERO | PCATCH, ret,
				    "ncladvl");
				if (error)
					return (EINTR);
				NFSVOPLOCK(vp, LK_EXCLUSIVE | LK_RETRY);
				if (vp->v_iflag & VI_DOOMED) {
					error = EBADF;
					goto out;
				}
			}
		} while (ret == NFSERR_DENIED && (ap->a_flags & F_WAIT) &&
		     ap->a_op == F_SETLK);
		if (ret == NFSERR_DENIED) {
			error = EAGAIN;
			goto out;
		} else if (ret == EINVAL || ret == EBADF || ret == EINTR) {
			error = ret;
			goto out;
		} else if (ret != 0) {
			error = EACCES;
			goto out;
		}

		/*
		 * Now, if we just got a lock, invalidate data in the buffer
		 * cache, as required, so that the coherency conforms with
		 * RFC3530 Sec. 9.3.2.
		 */
		if (ap->a_op == F_SETLK) {
			if ((np->n_flag & NMODIFIED) == 0) {
				np->n_attrstamp = 0;
				KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
				ret = VOP_GETATTR(vp, &va, cred);
			}
			if ((np->n_flag & NMODIFIED) || ret ||
			    np->n_change != va.va_filerev) {
				(void) ncl_vinvalbuf(vp, V_SAVE, td, 1);
				np->n_attrstamp = 0;
				KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
				ret = VOP_GETATTR(vp, &va, cred);
				if (!ret) {
					np->n_mtime = va.va_mtime;
					np->n_change = va.va_filerev;
				}
			}
			/* Mark that a file lock has been acquired. */
			NFSLOCKNODE(np);
			np->n_flag |= NHASBEENLOCKED;
			NFSUNLOCKNODE(np);
		}
	} else if (!NFS_ISV4(vp)) {
		if ((VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NOLOCKD) != 0) {
			size = VTONFS(vp)->n_size;
			NFSVOPUNLOCK(vp, 0);
			error = lf_advlock(ap, &(vp->v_lockf), size);
		} else {
			if (nfs_advlock_p != NULL)
				error = nfs_advlock_p(ap);
			else {
				NFSVOPUNLOCK(vp, 0);
				error = ENOLCK;
			}
		}
		if (error == 0 && ap->a_op == F_SETLK) {
			error = NFSVOPLOCK(vp, LK_SHARED);
			if (error == 0) {
				/* Mark that a file lock has been acquired. */
				NFSLOCKNODE(np);
				np->n_flag |= NHASBEENLOCKED;
				NFSUNLOCKNODE(np);
				NFSVOPUNLOCK(vp, 0);
			}
		}
		return (error);
	} else
		error = EOPNOTSUPP;
out:
	NFSVOPUNLOCK(vp, 0);
	return (error);
}