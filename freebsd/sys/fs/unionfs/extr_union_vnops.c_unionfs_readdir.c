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
typedef  int /*<<< orphan*/  u_long ;
struct vop_readdir_args {int* a_eofflag; int* a_ncookies; int /*<<< orphan*/ ** a_cookies; int /*<<< orphan*/  a_cred; struct vnode* a_vp; struct uio* a_uio; } ;
struct vnode {scalar_t__ v_type; } ;
struct vattr {int va_flags; } ;
struct unionfs_node_status {scalar_t__ uns_upper_opencnt; scalar_t__ uns_lower_opencnt; int uns_readdir_status; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;
struct uio {int uio_offset; int uio_resid; struct thread* uio_td; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int EBADF ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (struct vnode*) ; 
 int LK_DOWNGRADE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_UPGRADE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct vnode* NULLVP ; 
 int OPAQUE ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 scalar_t__ VDIR ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int VOP_READDIR (struct vnode*,struct uio*,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ **) ; 
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unionfs_get_node_status (struct unionfs_node*,struct thread*,struct unionfs_node_status**) ; 
 int /*<<< orphan*/  unionfs_tryrem_node_status (struct unionfs_node*,struct unionfs_node_status*) ; 
 scalar_t__ vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
unionfs_readdir(struct vop_readdir_args *ap)
{
	int		error;
	int		eofflag;
	int		locked;
	int		uio_offset_bk;
	struct unionfs_node *unp;
	struct unionfs_node_status *unsp;
	struct uio     *uio;
	struct vnode   *vp;
	struct vnode   *uvp;
	struct vnode   *lvp;
	struct thread  *td;
	struct vattr    va;

	int		ncookies_bk;
	u_long         *cookies_bk;

	UNIONFS_INTERNAL_DEBUG("unionfs_readdir: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	error = 0;
	eofflag = 0;
	locked = 0;
	uio_offset_bk = 0;
	uio = ap->a_uio;
	uvp = NULLVP;
	lvp = NULLVP;
	td = uio->uio_td;
	ncookies_bk = 0;
	cookies_bk = NULL;

	vp = ap->a_vp;
	if (vp->v_type != VDIR)
		return (ENOTDIR);

	/* check the open count. unionfs needs to open before readdir. */
	if (VOP_ISLOCKED(vp) != LK_EXCLUSIVE) {
		if (vn_lock(vp, LK_UPGRADE) != 0)
			vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		locked = 1;
	}
	unp = VTOUNIONFS(vp);
	if (unp == NULL)
		error = EBADF;
	else {
		uvp = unp->un_uppervp;
		lvp = unp->un_lowervp;
		unionfs_get_node_status(unp, td, &unsp);
		if ((uvp != NULLVP && unsp->uns_upper_opencnt <= 0) ||
			(lvp != NULLVP && unsp->uns_lower_opencnt <= 0)) {
			unionfs_tryrem_node_status(unp, unsp);
			error = EBADF;
		}
	}
	if (locked)
		vn_lock(vp, LK_DOWNGRADE | LK_RETRY);
	if (error != 0)
		goto unionfs_readdir_exit;

	/* check opaque */
	if (uvp != NULLVP && lvp != NULLVP) {
		if ((error = VOP_GETATTR(uvp, &va, ap->a_cred)) != 0)
			goto unionfs_readdir_exit;
		if (va.va_flags & OPAQUE)
			lvp = NULLVP;
	}

	/* upper only */
	if (uvp != NULLVP && lvp == NULLVP) {
		error = VOP_READDIR(uvp, uio, ap->a_cred, ap->a_eofflag,
		    ap->a_ncookies, ap->a_cookies);
		unsp->uns_readdir_status = 0;

		goto unionfs_readdir_exit;
	}

	/* lower only */
	if (uvp == NULLVP && lvp != NULLVP) {
		error = VOP_READDIR(lvp, uio, ap->a_cred, ap->a_eofflag,
		    ap->a_ncookies, ap->a_cookies);
		unsp->uns_readdir_status = 2;

		goto unionfs_readdir_exit;
	}

	/*
	 * readdir upper and lower
	 */
	KASSERT(uvp != NULLVP, ("unionfs_readdir: null upper vp"));
	KASSERT(lvp != NULLVP, ("unionfs_readdir: null lower vp"));
	if (uio->uio_offset == 0)
		unsp->uns_readdir_status = 0;

	if (unsp->uns_readdir_status == 0) {
		/* read upper */
		error = VOP_READDIR(uvp, uio, ap->a_cred, &eofflag,
				    ap->a_ncookies, ap->a_cookies);

		if (error != 0 || eofflag == 0)
			goto unionfs_readdir_exit;
		unsp->uns_readdir_status = 1;

		/*
		 * UFS(and other FS) needs size of uio_resid larger than
		 * DIRBLKSIZ.
		 * size of DIRBLKSIZ equals DEV_BSIZE.
		 * (see: ufs/ufs/ufs_vnops.c ufs_readdir func , ufs/ufs/dir.h)
		 */
		if (uio->uio_resid <= (uio->uio_resid & (DEV_BSIZE -1)))
			goto unionfs_readdir_exit;

		/*
		 * Backup cookies.
		 * It prepares to readdir in lower.
		 */
		if (ap->a_ncookies != NULL) {
			ncookies_bk = *(ap->a_ncookies);
			*(ap->a_ncookies) = 0;
		}
		if (ap->a_cookies != NULL) {
			cookies_bk = *(ap->a_cookies);
			*(ap->a_cookies) = NULL;
		}
	}

	/* initialize for readdir in lower */
	if (unsp->uns_readdir_status == 1) {
		unsp->uns_readdir_status = 2;
		/*
		 * Backup uio_offset. See the comment after the
		 * VOP_READDIR call on the lower layer.
		 */
		uio_offset_bk = uio->uio_offset;
		uio->uio_offset = 0;
	}

	if (lvp == NULLVP) {
		error = EBADF;
		goto unionfs_readdir_exit;
	}
	/* read lower */
	error = VOP_READDIR(lvp, uio, ap->a_cred, ap->a_eofflag,
			    ap->a_ncookies, ap->a_cookies);

	/*
	 * We can't return an uio_offset of 0: this would trigger an
	 * infinite loop, because the next call to unionfs_readdir would
	 * always restart with the upper layer (uio_offset == 0) and
	 * always return some data.
	 *
	 * This happens when the lower layer root directory is removed.
	 * (A root directory deleting of unionfs should not be permitted.
	 *  But current VFS can not do it.)
	 */
	if (uio->uio_offset == 0)
		uio->uio_offset = uio_offset_bk;

	if (cookies_bk != NULL) {
		/* merge cookies */
		int		size;
		u_long         *newcookies, *pos;

		size = *(ap->a_ncookies) + ncookies_bk;
		newcookies = (u_long *) malloc(size * sizeof(u_long),
		    M_TEMP, M_WAITOK);
		pos = newcookies;

		memcpy(pos, cookies_bk, ncookies_bk * sizeof(u_long));
		pos += ncookies_bk;
		memcpy(pos, *(ap->a_cookies), *(ap->a_ncookies) * sizeof(u_long));
		free(cookies_bk, M_TEMP);
		free(*(ap->a_cookies), M_TEMP);
		*(ap->a_ncookies) = size;
		*(ap->a_cookies) = newcookies;
	}

unionfs_readdir_exit:
	if (error != 0 && ap->a_eofflag != NULL)
		*(ap->a_eofflag) = 1;

	UNIONFS_INTERNAL_DEBUG("unionfs_readdir: leave (%d)\n", error);

	return (error);
}