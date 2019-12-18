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
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct vop_open_args {int a_mode; int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; int v_writecount; int /*<<< orphan*/ * v_object; int /*<<< orphan*/  v_mount; } ;
struct vattr {scalar_t__ va_filerev; int /*<<< orphan*/  va_size; int /*<<< orphan*/  va_mtime; } ;
struct ucred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  na_mtime; } ;
struct nfsnode {int n_flag; scalar_t__ n_change; scalar_t__ n_directio_opens; TYPE_1__ n_vattr; int /*<<< orphan*/  n_mtime; struct ucred* n_writecred; scalar_t__ n_direofoffset; scalar_t__ n_attrstamp; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int FWRITE ; 
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 scalar_t__ NFSHASPNFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 scalar_t__ NFS_TIMESPEC_COMPARE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NMODIFIED ; 
 int NNONCACHE ; 
 int NWRITEOPENED ; 
 int /*<<< orphan*/  OBJPC_SYNC ; 
 int O_DIRECT ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VFSTONFS (int /*<<< orphan*/ ) ; 
 scalar_t__ VLNK ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  ncl_flush (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ncl_vinvalbuf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ newnfs_directio_enable ; 
 int nfscl_maperr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrpc_close (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrpc_open (struct vnode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_mightbedirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_page_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_create_vobject (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_open(struct vop_open_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct nfsnode *np = VTONFS(vp);
	struct vattr vattr;
	int error;
	int fmode = ap->a_mode;
	struct ucred *cred;
	vm_object_t obj;

	if (vp->v_type != VREG && vp->v_type != VDIR && vp->v_type != VLNK)
		return (EOPNOTSUPP);

	/*
	 * For NFSv4, we need to do the Open Op before cache validation,
	 * so that we conform to RFC3530 Sec. 9.3.1.
	 */
	if (NFS_ISV4(vp)) {
		error = nfsrpc_open(vp, fmode, ap->a_cred, ap->a_td);
		if (error) {
			error = nfscl_maperr(ap->a_td, error, (uid_t)0,
			    (gid_t)0);
			return (error);
		}
	}

	/*
	 * Now, if this Open will be doing reading, re-validate/flush the
	 * cache, so that Close/Open coherency is maintained.
	 */
	NFSLOCKNODE(np);
	if (np->n_flag & NMODIFIED) {
		NFSUNLOCKNODE(np);
		error = ncl_vinvalbuf(vp, V_SAVE, ap->a_td, 1);
		if (error == EINTR || error == EIO) {
			if (NFS_ISV4(vp))
				(void) nfsrpc_close(vp, 0, ap->a_td);
			return (error);
		}
		NFSLOCKNODE(np);
		np->n_attrstamp = 0;
		KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
		if (vp->v_type == VDIR)
			np->n_direofoffset = 0;
		NFSUNLOCKNODE(np);
		error = VOP_GETATTR(vp, &vattr, ap->a_cred);
		if (error) {
			if (NFS_ISV4(vp))
				(void) nfsrpc_close(vp, 0, ap->a_td);
			return (error);
		}
		NFSLOCKNODE(np);
		np->n_mtime = vattr.va_mtime;
		if (NFS_ISV4(vp))
			np->n_change = vattr.va_filerev;
	} else {
		NFSUNLOCKNODE(np);
		error = VOP_GETATTR(vp, &vattr, ap->a_cred);
		if (error) {
			if (NFS_ISV4(vp))
				(void) nfsrpc_close(vp, 0, ap->a_td);
			return (error);
		}
		NFSLOCKNODE(np);
		if ((NFS_ISV4(vp) && np->n_change != vattr.va_filerev) ||
		    NFS_TIMESPEC_COMPARE(&np->n_mtime, &vattr.va_mtime)) {
			if (vp->v_type == VDIR)
				np->n_direofoffset = 0;
			NFSUNLOCKNODE(np);
			error = ncl_vinvalbuf(vp, V_SAVE, ap->a_td, 1);
			if (error == EINTR || error == EIO) {
				if (NFS_ISV4(vp))
					(void) nfsrpc_close(vp, 0, ap->a_td);
				return (error);
			}
			NFSLOCKNODE(np);
			np->n_mtime = vattr.va_mtime;
			if (NFS_ISV4(vp))
				np->n_change = vattr.va_filerev;
		}
	}

	/*
	 * If the object has >= 1 O_DIRECT active opens, we disable caching.
	 */
	if (newnfs_directio_enable && (fmode & O_DIRECT) &&
	    (vp->v_type == VREG)) {
		if (np->n_directio_opens == 0) {
			NFSUNLOCKNODE(np);
			error = ncl_vinvalbuf(vp, V_SAVE, ap->a_td, 1);
			if (error) {
				if (NFS_ISV4(vp))
					(void) nfsrpc_close(vp, 0, ap->a_td);
				return (error);
			}
			NFSLOCKNODE(np);
			np->n_flag |= NNONCACHE;
		}
		np->n_directio_opens++;
	}

	/* If opened for writing via NFSv4.1 or later, mark that for pNFS. */
	if (NFSHASPNFS(VFSTONFS(vp->v_mount)) && (fmode & FWRITE) != 0)
		np->n_flag |= NWRITEOPENED;

	/*
	 * If this is an open for writing, capture a reference to the
	 * credentials, so they can be used by ncl_putpages(). Using
	 * these write credentials is preferable to the credentials of
	 * whatever thread happens to be doing the VOP_PUTPAGES() since
	 * the write RPCs are less likely to fail with EACCES.
	 */
	if ((fmode & FWRITE) != 0) {
		cred = np->n_writecred;
		np->n_writecred = crhold(ap->a_cred);
	} else
		cred = NULL;
	NFSUNLOCKNODE(np);

	if (cred != NULL)
		crfree(cred);
	vnode_create_vobject(vp, vattr.va_size, ap->a_td);

	/*
	 * If the text file has been mmap'd, flush any dirty pages to the
	 * buffer cache and then...
	 * Make sure all writes are pushed to the NFS server.  If this is not
	 * done, the modify time of the file can change while the text
	 * file is being executed.  This will cause the process that is
	 * executing the text file to be terminated.
	 */
	if (vp->v_writecount <= -1) {
		if ((obj = vp->v_object) != NULL &&
		    vm_object_mightbedirty(obj)) {
			VM_OBJECT_WLOCK(obj);
			vm_object_page_clean(obj, 0, 0, OBJPC_SYNC);
			VM_OBJECT_WUNLOCK(obj);
		}

		/* Now, flush the buffer cache. */
		ncl_flush(vp, MNT_WAIT, curthread, 0, 0);

		/* And, finally, make sure that n_mtime is up to date. */
		np = VTONFS(vp);
		NFSLOCKNODE(np);
		np->n_mtime = np->n_vattr.na_mtime;
		NFSUNLOCKNODE(np);
	}
	return (0);
}