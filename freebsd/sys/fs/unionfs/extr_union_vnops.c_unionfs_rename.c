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
struct vop_rename_args {struct componentname* a_tcnp; struct vnode* a_tvp; struct vnode* a_tdvp; struct componentname* a_fcnp; struct vnode* a_fvp; struct vnode* a_fdvp; } ;
struct vnode {scalar_t__ v_mount; int v_type; int /*<<< orphan*/ * v_op; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;
struct unionfs_mount {int dummy; } ;
struct thread {int dummy; } ;
struct componentname {int cn_flags; int /*<<< orphan*/  cn_cred; } ;

/* Variables and functions */
 int DOWHITEOUT ; 
 int EINVAL ; 
 int ENODEV ; 
 int EXDEV ; 
 int HASBUF ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (struct vnode*) ; 
 int LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_RELEASE ; 
 int LK_RETRY ; 
 struct unionfs_mount* MOUNTTOUNIONFSMOUNT (scalar_t__) ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
#define  VDIR 129 
 int VOP_RENAME (struct vnode*,struct vnode*,struct componentname*,struct vnode*,struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
#define  VREG 128 
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  panic (char*) ; 
 int unionfs_copyfile (struct unionfs_node*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int unionfs_mkshadowdir (struct unionfs_mount*,struct vnode*,struct unionfs_node*,struct componentname*,struct thread*) ; 
 int unionfs_relookup_for_delete (struct vnode*,struct componentname*,struct thread*) ; 
 int unionfs_relookup_for_rename (struct vnode*,struct componentname*,struct thread*) ; 
 int /*<<< orphan*/  unionfs_vnodeops ; 
 int vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
unionfs_rename(struct vop_rename_args *ap)
{
	int		error;
	struct vnode   *fdvp;
	struct vnode   *fvp;
	struct componentname *fcnp;
	struct vnode   *tdvp;
	struct vnode   *tvp;
	struct componentname *tcnp;
	struct vnode   *ltdvp;
	struct vnode   *ltvp;
	struct thread  *td;

	/* rename target vnodes */
	struct vnode   *rfdvp;
	struct vnode   *rfvp;
	struct vnode   *rtdvp;
	struct vnode   *rtvp;

	int		needrelookup;
	struct unionfs_mount *ump;
	struct unionfs_node *unp;

	UNIONFS_INTERNAL_DEBUG("unionfs_rename: enter\n");

	error = 0;
	fdvp = ap->a_fdvp;
	fvp = ap->a_fvp;
	fcnp = ap->a_fcnp;
	tdvp = ap->a_tdvp;
	tvp = ap->a_tvp;
	tcnp = ap->a_tcnp;
	ltdvp = NULLVP;
	ltvp = NULLVP;
	td = curthread;
	rfdvp = fdvp;
	rfvp = fvp;
	rtdvp = tdvp;
	rtvp = tvp;
	needrelookup = 0;

#ifdef DIAGNOSTIC
	if (!(fcnp->cn_flags & HASBUF) || !(tcnp->cn_flags & HASBUF))
		panic("unionfs_rename: no name");
#endif

	/* check for cross device rename */
	if (fvp->v_mount != tdvp->v_mount ||
	    (tvp != NULLVP && fvp->v_mount != tvp->v_mount)) {
		if (fvp->v_op != &unionfs_vnodeops)
			error = ENODEV;
		else
			error = EXDEV;
		goto unionfs_rename_abort;
	}

	/* Renaming a file to itself has no effect. */
	if (fvp == tvp)
		goto unionfs_rename_abort;

	/*
	 * from/to vnode is unionfs node.
	 */

	KASSERT_UNIONFS_VNODE(fdvp);
	KASSERT_UNIONFS_VNODE(fvp);
	KASSERT_UNIONFS_VNODE(tdvp);
	if (tvp != NULLVP)
		KASSERT_UNIONFS_VNODE(tvp);

	unp = VTOUNIONFS(fdvp);
#ifdef UNIONFS_IDBG_RENAME
	UNIONFS_INTERNAL_DEBUG("fdvp=%p, ufdvp=%p, lfdvp=%p\n", fdvp, unp->un_uppervp, unp->un_lowervp);
#endif
	if (unp->un_uppervp == NULLVP) {
		error = ENODEV;
		goto unionfs_rename_abort;
	}
	rfdvp = unp->un_uppervp;
	vref(rfdvp);

	unp = VTOUNIONFS(fvp);
#ifdef UNIONFS_IDBG_RENAME
	UNIONFS_INTERNAL_DEBUG("fvp=%p, ufvp=%p, lfvp=%p\n", fvp, unp->un_uppervp, unp->un_lowervp);
#endif
	ump = MOUNTTOUNIONFSMOUNT(fvp->v_mount);
	if (unp->un_uppervp == NULLVP) {
		switch (fvp->v_type) {
		case VREG:
			if ((error = vn_lock(fvp, LK_EXCLUSIVE)) != 0)
				goto unionfs_rename_abort;
			error = unionfs_copyfile(unp, 1, fcnp->cn_cred, td);
			VOP_UNLOCK(fvp, LK_RELEASE);
			if (error != 0)
				goto unionfs_rename_abort;
			break;
		case VDIR:
			if ((error = vn_lock(fvp, LK_EXCLUSIVE)) != 0)
				goto unionfs_rename_abort;
			error = unionfs_mkshadowdir(ump, rfdvp, unp, fcnp, td);
			VOP_UNLOCK(fvp, LK_RELEASE);
			if (error != 0)
				goto unionfs_rename_abort;
			break;
		default:
			error = ENODEV;
			goto unionfs_rename_abort;
		}

		needrelookup = 1;
	}

	if (unp->un_lowervp != NULLVP)
		fcnp->cn_flags |= DOWHITEOUT;
	rfvp = unp->un_uppervp;
	vref(rfvp);

	unp = VTOUNIONFS(tdvp);
#ifdef UNIONFS_IDBG_RENAME
	UNIONFS_INTERNAL_DEBUG("tdvp=%p, utdvp=%p, ltdvp=%p\n", tdvp, unp->un_uppervp, unp->un_lowervp);
#endif
	if (unp->un_uppervp == NULLVP) {
		error = ENODEV;
		goto unionfs_rename_abort;
	}
	rtdvp = unp->un_uppervp;
	ltdvp = unp->un_lowervp;
	vref(rtdvp);

	if (tdvp == tvp) {
		rtvp = rtdvp;
		vref(rtvp);
	} else if (tvp != NULLVP) {
		unp = VTOUNIONFS(tvp);
#ifdef UNIONFS_IDBG_RENAME
		UNIONFS_INTERNAL_DEBUG("tvp=%p, utvp=%p, ltvp=%p\n", tvp, unp->un_uppervp, unp->un_lowervp);
#endif
		if (unp->un_uppervp == NULLVP)
			rtvp = NULLVP;
		else {
			if (tvp->v_type == VDIR) {
				error = EINVAL;
				goto unionfs_rename_abort;
			}
			rtvp = unp->un_uppervp;
			ltvp = unp->un_lowervp;
			vref(rtvp);
		}
	}

	if (rfvp == rtvp)
		goto unionfs_rename_abort;

	if (needrelookup != 0) {
		if ((error = vn_lock(fdvp, LK_EXCLUSIVE)) != 0)
			goto unionfs_rename_abort;
		error = unionfs_relookup_for_delete(fdvp, fcnp, td);
		VOP_UNLOCK(fdvp, LK_RELEASE);
		if (error != 0)
			goto unionfs_rename_abort;

		/* Locke of tvp is canceled in order to avoid recursive lock. */
		if (tvp != NULLVP && tvp != tdvp)
			VOP_UNLOCK(tvp, LK_RELEASE);
		error = unionfs_relookup_for_rename(tdvp, tcnp, td);
		if (tvp != NULLVP && tvp != tdvp)
			vn_lock(tvp, LK_EXCLUSIVE | LK_RETRY);
		if (error != 0)
			goto unionfs_rename_abort;
	}

	error = VOP_RENAME(rfdvp, rfvp, fcnp, rtdvp, rtvp, tcnp);

	if (error == 0) {
		if (rtvp != NULLVP && rtvp->v_type == VDIR)
			cache_purge(tdvp);
		if (fvp->v_type == VDIR && fdvp != tdvp)
			cache_purge(fdvp);
	}

	if (ltdvp != NULLVP)
		VOP_UNLOCK(ltdvp, LK_RELEASE);
	if (tdvp != rtdvp)
		vrele(tdvp);
	if (ltvp != NULLVP)
		VOP_UNLOCK(ltvp, LK_RELEASE);
	if (tvp != rtvp && tvp != NULLVP) {
		if (rtvp == NULLVP)
			vput(tvp);
		else
			vrele(tvp);
	}
	if (fdvp != rfdvp)
		vrele(fdvp);
	if (fvp != rfvp)
		vrele(fvp);

	UNIONFS_INTERNAL_DEBUG("unionfs_rename: leave (%d)\n", error);

	return (error);

unionfs_rename_abort:
	vput(tdvp);
	if (tdvp != rtdvp)
		vrele(rtdvp);
	if (tvp != NULLVP) {
		if (tdvp != tvp)
			vput(tvp);
		else
			vrele(tvp);
	}
	if (tvp != rtvp && rtvp != NULLVP)
		vrele(rtvp);
	if (fdvp != rfdvp)
		vrele(rfdvp);
	if (fvp != rfvp)
		vrele(rfvp);
	vrele(fdvp);
	vrele(fvp);

	UNIONFS_INTERNAL_DEBUG("unionfs_rename: leave (%d)\n", error);

	return (error);
}