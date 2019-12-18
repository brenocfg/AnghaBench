#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct vattr {TYPE_2__ va_mtime; } ;
struct uio {scalar_t__ uio_segflg; scalar_t__ uio_resid; scalar_t__ uio_offset; struct thread* uio_td; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;
struct smbnode {int n_flag; int /*<<< orphan*/  n_fid; TYPE_1__ n_mtime; } ;
struct smbmount {int /*<<< orphan*/  sm_share; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int LK_DOWNGRADE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int LK_UPGRADE ; 
 int NMODIFIED ; 
 int /*<<< orphan*/  SMBFSERR (char*) ; 
 scalar_t__ UIO_NOCOPY ; 
 scalar_t__ VDIR ; 
 struct smbmount* VFSTOSMBFS (int /*<<< orphan*/ ) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 scalar_t__ VREG ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,struct ucred*) ; 
 int smb_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*,struct smb_cred*) ; 
 int /*<<< orphan*/  smbfs_attr_cacheremove (struct vnode*) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 
 int smbfs_readvdir (struct vnode*,struct uio*,struct ucred*) ; 
 int smbfs_vinvalbuf (struct vnode*,struct thread*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

int
smbfs_readvnode(struct vnode *vp, struct uio *uiop, struct ucred *cred)
{
	struct smbmount *smp = VFSTOSMBFS(vp->v_mount);
	struct smbnode *np = VTOSMB(vp);
	struct thread *td;
	struct vattr vattr;
	struct smb_cred *scred;
	int error, lks;

	/*
	 * Protect against method which is not supported for now
	 */
	if (uiop->uio_segflg == UIO_NOCOPY)
		return EOPNOTSUPP;

	if (vp->v_type != VREG && vp->v_type != VDIR) {
		SMBFSERR("vn types other than VREG or VDIR are unsupported !\n");
		return EIO;
	}
	if (uiop->uio_resid == 0)
		return 0;
	if (uiop->uio_offset < 0)
		return EINVAL;
/*	if (uiop->uio_offset + uiop->uio_resid > smp->nm_maxfilesize)
		return EFBIG;*/
	td = uiop->uio_td;
	if (vp->v_type == VDIR) {
		lks = LK_EXCLUSIVE;	/* lockstatus(vp->v_vnlock); */
		if (lks == LK_SHARED)
			vn_lock(vp, LK_UPGRADE | LK_RETRY);
		error = smbfs_readvdir(vp, uiop, cred);
		if (lks == LK_SHARED)
			vn_lock(vp, LK_DOWNGRADE | LK_RETRY);
		return error;
	}

/*	biosize = SSTOCN(smp->sm_share)->sc_txmax;*/
	if (np->n_flag & NMODIFIED) {
		smbfs_attr_cacheremove(vp);
		error = VOP_GETATTR(vp, &vattr, cred);
		if (error)
			return error;
		np->n_mtime.tv_sec = vattr.va_mtime.tv_sec;
	} else {
		error = VOP_GETATTR(vp, &vattr, cred);
		if (error)
			return error;
		if (np->n_mtime.tv_sec != vattr.va_mtime.tv_sec) {
			error = smbfs_vinvalbuf(vp, td);
			if (error)
				return error;
			np->n_mtime.tv_sec = vattr.va_mtime.tv_sec;
		}
	}
	scred = smbfs_malloc_scred();
	smb_makescred(scred, td, cred);
	error = smb_read(smp->sm_share, np->n_fid, uiop, scred);
	smbfs_free_scred(scred);
	return (error);
}