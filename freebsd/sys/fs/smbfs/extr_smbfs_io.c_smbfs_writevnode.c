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
struct uio {scalar_t__ uio_offset; scalar_t__ uio_resid; struct thread* uio_td; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct smbnode {int n_flag; scalar_t__ n_size; int /*<<< orphan*/  n_fid; } ;
struct smbmount {int /*<<< orphan*/  sm_share; } ;
struct smb_cred {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 int EIO ; 
 int IO_APPEND ; 
 int IO_SYNC ; 
 int NMODIFIED ; 
 int /*<<< orphan*/  SMBERROR (char*) ; 
 int /*<<< orphan*/  SMBVDEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int VOP_GETATTR (struct vnode*,int /*<<< orphan*/ *,struct ucred*) ; 
 scalar_t__ VREG ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 struct smbmount* VTOSMBFS (struct vnode*) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,struct ucred*) ; 
 int smb_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*,struct smb_cred*) ; 
 int /*<<< orphan*/  smbfs_attr_cacheremove (struct vnode*) ; 
 int /*<<< orphan*/  smbfs_free_scred (struct smb_cred*) ; 
 struct smb_cred* smbfs_malloc_scred () ; 
 int smbfs_vinvalbuf (struct vnode*,struct thread*) ; 
 int /*<<< orphan*/  vattr ; 
 scalar_t__ vn_rlimit_fsize (struct vnode*,struct uio*,struct thread*) ; 
 int /*<<< orphan*/  vnode_pager_setsize (struct vnode*,scalar_t__) ; 

int
smbfs_writevnode(struct vnode *vp, struct uio *uiop,
	struct ucred *cred, int ioflag)
{
	struct smbmount *smp = VTOSMBFS(vp);
	struct smbnode *np = VTOSMB(vp);
	struct smb_cred *scred;
	struct thread *td;
	int error = 0;

	if (vp->v_type != VREG) {
		SMBERROR("vn types other than VREG unsupported !\n");
		return EIO;
	}
	SMBVDEBUG("ofs=%jd,resid=%zd\n", (intmax_t)uiop->uio_offset, 
	    uiop->uio_resid);
	if (uiop->uio_offset < 0)
		return EINVAL;
/*	if (uiop->uio_offset + uiop->uio_resid > smp->nm_maxfilesize)
		return (EFBIG);*/
	td = uiop->uio_td;
	if (ioflag & (IO_APPEND | IO_SYNC)) {
		if (np->n_flag & NMODIFIED) {
			smbfs_attr_cacheremove(vp);
			error = smbfs_vinvalbuf(vp, td);
			if (error)
				return error;
		}
		if (ioflag & IO_APPEND) {
#ifdef notyet
			/*
			 * File size can be changed by another client
			 */
			smbfs_attr_cacheremove(vp);
			error = VOP_GETATTR(vp, &vattr, cred);
			if (error) return (error);
#endif
			uiop->uio_offset = np->n_size;
		}
	}
	if (uiop->uio_resid == 0)
		return 0;

	if (vn_rlimit_fsize(vp, uiop, td))
		return (EFBIG);
	
	scred = smbfs_malloc_scred();
	smb_makescred(scred, td, cred);
	error = smb_write(smp->sm_share, np->n_fid, uiop, scred);
	smbfs_free_scred(scred);
	SMBVDEBUG("after: ofs=%jd,resid=%zd\n", (intmax_t)uiop->uio_offset, 
	    uiop->uio_resid);
	if (!error) {
		if (uiop->uio_offset > np->n_size) {
			np->n_size = uiop->uio_offset;
			vnode_pager_setsize(vp, np->n_size);
		}
	}
	return error;
}