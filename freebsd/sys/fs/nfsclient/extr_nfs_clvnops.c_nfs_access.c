#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct vop_access_args {int a_accmode; TYPE_4__* a_cred; int /*<<< orphan*/  a_td; struct vnode* a_vp; } ;
struct vnode {int v_type; TYPE_1__* v_mount; } ;
struct uio {int uio_iovcnt; int uio_resid; int /*<<< orphan*/  uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct nfsnode {scalar_t__ n_size; TYPE_2__* n_accesscache; } ;
struct iovec {char* iov_base; int iov_len; } ;
struct TYPE_11__ {scalar_t__ cr_uid; } ;
struct TYPE_10__ {int /*<<< orphan*/  accesscache_misses; int /*<<< orphan*/  accesscache_hits; } ;
struct TYPE_9__ {scalar_t__ uid; scalar_t__ stamp; int mode; } ;
struct TYPE_8__ {int mnt_flag; } ;

/* Variables and functions */
 int EACCES ; 
 int EROFS ; 
 int /*<<< orphan*/  KDTRACE_NFS_ACCESSCACHE_GET_HIT (struct vnode*,scalar_t__,int) ; 
 int /*<<< orphan*/  KDTRACE_NFS_ACCESSCACHE_GET_MISS (struct vnode*,scalar_t__,int) ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NFSACCESS_DELETE ; 
 int NFSACCESS_EXECUTE ; 
 int NFSACCESS_EXTEND ; 
 int NFSACCESS_LOOKUP ; 
 int NFSACCESS_MODIFY ; 
 int NFSACCESS_READ ; 
 int /*<<< orphan*/  NFSINCRGLOBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NFS_ACCESSCACHESIZE ; 
 int NFS_DIRBLKSIZ ; 
 int NFS_ISV34 (struct vnode*) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VAPPEND ; 
 int VDELETE ; 
 int VDELETE_CHILD ; 
#define  VDIR 130 
 int VEXEC ; 
#define  VLNK 129 
 int VREAD ; 
#define  VREG 128 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int VWRITE ; 
 int VWRITE_ACL ; 
 int VWRITE_ATTRIBUTES ; 
 int VWRITE_NAMED_ATTRS ; 
 int VWRITE_OWNER ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ncl_readdirrpc (struct vnode*,struct uio*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ncl_readlinkrpc (struct vnode*,struct uio*,TYPE_4__*) ; 
 int ncl_readrpc (struct vnode*,struct uio*,TYPE_4__*) ; 
 int nfs34_access_otw (struct vnode*,int,int /*<<< orphan*/ ,TYPE_4__*,int*) ; 
 scalar_t__ nfsaccess_cache_timeout ; 
 int nfsspec_access (struct vop_access_args*) ; 
 TYPE_3__ nfsstatsv1 ; 
 scalar_t__ time_second ; 

__attribute__((used)) static int
nfs_access(struct vop_access_args *ap)
{
	struct vnode *vp = ap->a_vp;
	int error = 0, i, gotahit;
	u_int32_t mode, wmode, rmode;
	int v34 = NFS_ISV34(vp);
	struct nfsnode *np = VTONFS(vp);

	/*
	 * Disallow write attempts on filesystems mounted read-only;
	 * unless the file is a socket, fifo, or a block or character
	 * device resident on the filesystem.
	 */
	if ((ap->a_accmode & (VWRITE | VAPPEND | VWRITE_NAMED_ATTRS |
	    VDELETE_CHILD | VWRITE_ATTRIBUTES | VDELETE | VWRITE_ACL |
	    VWRITE_OWNER)) != 0 && (vp->v_mount->mnt_flag & MNT_RDONLY) != 0) {
		switch (vp->v_type) {
		case VREG:
		case VDIR:
		case VLNK:
			return (EROFS);
		default:
			break;
		}
	}
	/*
	 * For nfs v3 or v4, check to see if we have done this recently, and if
	 * so return our cached result instead of making an ACCESS call.
	 * If not, do an access rpc, otherwise you are stuck emulating
	 * ufs_access() locally using the vattr. This may not be correct,
	 * since the server may apply other access criteria such as
	 * client uid-->server uid mapping that we do not know about.
	 */
	if (v34) {
		if (ap->a_accmode & VREAD)
			mode = NFSACCESS_READ;
		else
			mode = 0;
		if (vp->v_type != VDIR) {
			if (ap->a_accmode & VWRITE)
				mode |= (NFSACCESS_MODIFY | NFSACCESS_EXTEND);
			if (ap->a_accmode & VAPPEND)
				mode |= NFSACCESS_EXTEND;
			if (ap->a_accmode & VEXEC)
				mode |= NFSACCESS_EXECUTE;
			if (ap->a_accmode & VDELETE)
				mode |= NFSACCESS_DELETE;
		} else {
			if (ap->a_accmode & VWRITE)
				mode |= (NFSACCESS_MODIFY | NFSACCESS_EXTEND);
			if (ap->a_accmode & VAPPEND)
				mode |= NFSACCESS_EXTEND;
			if (ap->a_accmode & VEXEC)
				mode |= NFSACCESS_LOOKUP;
			if (ap->a_accmode & VDELETE)
				mode |= NFSACCESS_DELETE;
			if (ap->a_accmode & VDELETE_CHILD)
				mode |= NFSACCESS_MODIFY;
		}
		/* XXX safety belt, only make blanket request if caching */
		if (nfsaccess_cache_timeout > 0) {
			wmode = NFSACCESS_READ | NFSACCESS_MODIFY |
				NFSACCESS_EXTEND | NFSACCESS_EXECUTE |
				NFSACCESS_DELETE | NFSACCESS_LOOKUP;
		} else {
			wmode = mode;
		}

		/*
		 * Does our cached result allow us to give a definite yes to
		 * this request?
		 */
		gotahit = 0;
		NFSLOCKNODE(np);
		for (i = 0; i < NFS_ACCESSCACHESIZE; i++) {
			if (ap->a_cred->cr_uid == np->n_accesscache[i].uid) {
			    if (time_second < (np->n_accesscache[i].stamp
				+ nfsaccess_cache_timeout) &&
				(np->n_accesscache[i].mode & mode) == mode) {
				NFSINCRGLOBAL(nfsstatsv1.accesscache_hits);
				gotahit = 1;
			    }
			    break;
			}
		}
		NFSUNLOCKNODE(np);
#ifdef KDTRACE_HOOKS
		if (gotahit != 0)
			KDTRACE_NFS_ACCESSCACHE_GET_HIT(vp,
			    ap->a_cred->cr_uid, mode);
		else
			KDTRACE_NFS_ACCESSCACHE_GET_MISS(vp,
			    ap->a_cred->cr_uid, mode);
#endif
		if (gotahit == 0) {
			/*
			 * Either a no, or a don't know.  Go to the wire.
			 */
			NFSINCRGLOBAL(nfsstatsv1.accesscache_misses);
		        error = nfs34_access_otw(vp, wmode, ap->a_td,
			    ap->a_cred, &rmode);
			if (!error &&
			    (rmode & mode) != mode)
				error = EACCES;
		}
		return (error);
	} else {
		if ((error = nfsspec_access(ap)) != 0) {
			return (error);
		}
		/*
		 * Attempt to prevent a mapped root from accessing a file
		 * which it shouldn't.  We try to read a byte from the file
		 * if the user is root and the file is not zero length.
		 * After calling nfsspec_access, we should have the correct
		 * file size cached.
		 */
		NFSLOCKNODE(np);
		if (ap->a_cred->cr_uid == 0 && (ap->a_accmode & VREAD)
		    && VTONFS(vp)->n_size > 0) {
			struct iovec aiov;
			struct uio auio;
			char buf[1];

			NFSUNLOCKNODE(np);
			aiov.iov_base = buf;
			aiov.iov_len = 1;
			auio.uio_iov = &aiov;
			auio.uio_iovcnt = 1;
			auio.uio_offset = 0;
			auio.uio_resid = 1;
			auio.uio_segflg = UIO_SYSSPACE;
			auio.uio_rw = UIO_READ;
			auio.uio_td = ap->a_td;

			if (vp->v_type == VREG)
				error = ncl_readrpc(vp, &auio, ap->a_cred);
			else if (vp->v_type == VDIR) {
				char* bp;
				bp = malloc(NFS_DIRBLKSIZ, M_TEMP, M_WAITOK);
				aiov.iov_base = bp;
				aiov.iov_len = auio.uio_resid = NFS_DIRBLKSIZ;
				error = ncl_readdirrpc(vp, &auio, ap->a_cred,
				    ap->a_td);
				free(bp, M_TEMP);
			} else if (vp->v_type == VLNK)
				error = ncl_readlinkrpc(vp, &auio, ap->a_cred);
			else
				error = EACCES;
		} else
			NFSUNLOCKNODE(np);
		return (error);
	}
}