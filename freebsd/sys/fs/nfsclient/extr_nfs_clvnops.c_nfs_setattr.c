#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ u_quad_t ;
struct vop_setattr_args {int /*<<< orphan*/  a_cred; struct vattr* a_vap; struct vnode* a_vp; } ;
struct vnode {int v_type; TYPE_1__* v_mount; } ;
struct TYPE_7__ {scalar_t__ tv_sec; } ;
struct TYPE_6__ {scalar_t__ tv_sec; } ;
struct vattr {scalar_t__ va_flags; scalar_t__ va_uid; scalar_t__ va_gid; scalar_t__ va_mode; scalar_t__ va_size; TYPE_3__ va_atime; TYPE_2__ va_mtime; } ;
struct thread {int dummy; } ;
struct TYPE_8__ {scalar_t__ na_size; } ;
struct nfsnode {scalar_t__ n_size; int n_flag; TYPE_4__ n_vattr; } ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_5__ {int mnt_flag; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int EISDIR ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NMODIFIED ; 
#define  VBLK 132 
#define  VCHR 131 
#define  VDIR 130 
#define  VFIFO 129 
 scalar_t__ VNOVAL ; 
 int VREG ; 
#define  VSOCK 128 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  V_SAVE ; 
 struct thread* curthread ; 
 int ncl_meta_setsize (struct vnode*,struct thread*,scalar_t__) ; 
 int ncl_vinvalbuf (struct vnode*,int /*<<< orphan*/ ,struct thread*,int) ; 
 int nfs_setattrrpc (struct vnode*,struct vattr*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  nfscl_delegmodtime (struct vnode*) ; 
 int /*<<< orphan*/  vnode_pager_setsize (struct vnode*,scalar_t__) ; 

__attribute__((used)) static int
nfs_setattr(struct vop_setattr_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct nfsnode *np = VTONFS(vp);
	struct thread *td = curthread;	/* XXX */
	struct vattr *vap = ap->a_vap;
	int error = 0;
	u_quad_t tsize;

#ifndef nolint
	tsize = (u_quad_t)0;
#endif

	/*
	 * Setting of flags and marking of atimes are not supported.
	 */
	if (vap->va_flags != VNOVAL)
		return (EOPNOTSUPP);

	/*
	 * Disallow write attempts if the filesystem is mounted read-only.
	 */
  	if ((vap->va_flags != VNOVAL || vap->va_uid != (uid_t)VNOVAL ||
	    vap->va_gid != (gid_t)VNOVAL || vap->va_atime.tv_sec != VNOVAL ||
	    vap->va_mtime.tv_sec != VNOVAL || vap->va_mode != (mode_t)VNOVAL) &&
	    (vp->v_mount->mnt_flag & MNT_RDONLY))
		return (EROFS);
	if (vap->va_size != VNOVAL) {
 		switch (vp->v_type) {
 		case VDIR:
 			return (EISDIR);
 		case VCHR:
 		case VBLK:
 		case VSOCK:
 		case VFIFO:
			if (vap->va_mtime.tv_sec == VNOVAL &&
			    vap->va_atime.tv_sec == VNOVAL &&
			    vap->va_mode == (mode_t)VNOVAL &&
			    vap->va_uid == (uid_t)VNOVAL &&
			    vap->va_gid == (gid_t)VNOVAL)
				return (0);		
 			vap->va_size = VNOVAL;
 			break;
 		default:
			/*
			 * Disallow write attempts if the filesystem is
			 * mounted read-only.
			 */
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
			/*
			 *  We run vnode_pager_setsize() early (why?),
			 * we must set np->n_size now to avoid vinvalbuf
			 * V_SAVE races that might setsize a lower
			 * value.
			 */
			NFSLOCKNODE(np);
			tsize = np->n_size;
			NFSUNLOCKNODE(np);
			error = ncl_meta_setsize(vp, td, vap->va_size);
			NFSLOCKNODE(np);
 			if (np->n_flag & NMODIFIED) {
			    tsize = np->n_size;
			    NFSUNLOCKNODE(np);
			    error = ncl_vinvalbuf(vp, vap->va_size == 0 ?
			        0 : V_SAVE, td, 1);
			    if (error != 0) {
				    vnode_pager_setsize(vp, tsize);
				    return (error);
			    }
			    /*
			     * Call nfscl_delegmodtime() to set the modify time
			     * locally, as required.
			     */
			    nfscl_delegmodtime(vp);
 			} else
			    NFSUNLOCKNODE(np);
			/*
			 * np->n_size has already been set to vap->va_size
			 * in ncl_meta_setsize(). We must set it again since
			 * nfs_loadattrcache() could be called through
			 * ncl_meta_setsize() and could modify np->n_size.
			 */
			NFSLOCKNODE(np);
 			np->n_vattr.na_size = np->n_size = vap->va_size;
			NFSUNLOCKNODE(np);
  		}
  	} else {
		NFSLOCKNODE(np);
		if ((vap->va_mtime.tv_sec != VNOVAL || vap->va_atime.tv_sec != VNOVAL) && 
		    (np->n_flag & NMODIFIED) && vp->v_type == VREG) {
			NFSUNLOCKNODE(np);
			error = ncl_vinvalbuf(vp, V_SAVE, td, 1);
			if (error == EINTR || error == EIO)
				return (error);
		} else
			NFSUNLOCKNODE(np);
	}
	error = nfs_setattrrpc(vp, vap, ap->a_cred, td);
	if (error && vap->va_size != VNOVAL) {
		NFSLOCKNODE(np);
		np->n_size = np->n_vattr.na_size = tsize;
		vnode_pager_setsize(vp, tsize);
		NFSUNLOCKNODE(np);
	}
	return (error);
}