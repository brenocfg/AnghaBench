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
struct vop_lookup_args {struct vnode* a_dvp; struct vnode** a_vpp; struct componentname* a_cnp; } ;
struct vnode {scalar_t__ v_type; int v_vflag; struct devfs_dirent* v_data; struct mount* v_mount; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct mount {int dummy; } ;
struct devfs_mount {size_t dm_idx; int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {int de_flags; } ;
struct componentname {char* cn_nameptr; int cn_flags; int cn_nameiop; int cn_namelen; int cn_lkflags; int /*<<< orphan*/  cn_cred; struct thread* cn_thread; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {struct devfs_dirent** cdp_dirents; } ;

/* Variables and functions */
 int CREATE ; 
 int DELETE ; 
 scalar_t__ DEVFS_DMP_DROP (struct devfs_mount*) ; 
 int /*<<< orphan*/  DEVFS_DMP_HOLD (struct devfs_mount*) ; 
 int DE_WHITEOUT ; 
 int EINVAL ; 
 int EIO ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct cdev**) ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int LK_RETRY ; 
 int LK_TYPE_MASK ; 
 int LOCKPARENT ; 
 int LOOKUP ; 
 struct vnode* NULLVP ; 
 int RENAME ; 
 int SAVENAME ; 
 int /*<<< orphan*/  SPECNAMELEN ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VEXEC ; 
 struct devfs_mount* VFSTODEVFS (struct mount*) ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 int VV_ROOT ; 
 int /*<<< orphan*/  VWRITE ; 
 int WANTPARENT ; 
 TYPE_1__* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  clone_drain_lock ; 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_rel (struct cdev*) ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int devfs_allocv (struct devfs_dirent*,struct mount*,int,struct vnode**) ; 
 struct devfs_dirent* devfs_find (struct devfs_dirent*,char*,int,int /*<<< orphan*/ ) ; 
 char* devfs_fqpn (char*,struct devfs_mount*,struct devfs_dirent*,struct componentname*) ; 
 struct devfs_dirent* devfs_parent_dirent (struct devfs_dirent*) ; 
 scalar_t__ devfs_populate_vp (struct vnode*) ; 
 scalar_t__ devfs_prison_check (struct devfs_dirent*,struct thread*) ; 
 int /*<<< orphan*/  devfs_unmount_final (struct devfs_mount*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
devfs_lookupx(struct vop_lookup_args *ap, int *dm_unlock)
{
	struct componentname *cnp;
	struct vnode *dvp, **vpp;
	struct thread *td;
	struct devfs_dirent *de, *dd;
	struct devfs_dirent **dde;
	struct devfs_mount *dmp;
	struct mount *mp;
	struct cdev *cdev;
	int error, flags, nameiop, dvplocked;
	char specname[SPECNAMELEN + 1], *pname;

	cnp = ap->a_cnp;
	vpp = ap->a_vpp;
	dvp = ap->a_dvp;
	pname = cnp->cn_nameptr;
	td = cnp->cn_thread;
	flags = cnp->cn_flags;
	nameiop = cnp->cn_nameiop;
	mp = dvp->v_mount;
	dmp = VFSTODEVFS(mp);
	dd = dvp->v_data;
	*vpp = NULLVP;

	if ((flags & ISLASTCN) && nameiop == RENAME)
		return (EOPNOTSUPP);

	if (dvp->v_type != VDIR)
		return (ENOTDIR);

	if ((flags & ISDOTDOT) && (dvp->v_vflag & VV_ROOT))
		return (EIO);

	error = VOP_ACCESS(dvp, VEXEC, cnp->cn_cred, td);
	if (error)
		return (error);

	if (cnp->cn_namelen == 1 && *pname == '.') {
		if ((flags & ISLASTCN) && nameiop != LOOKUP)
			return (EINVAL);
		*vpp = dvp;
		VREF(dvp);
		return (0);
	}

	if (flags & ISDOTDOT) {
		if ((flags & ISLASTCN) && nameiop != LOOKUP)
			return (EINVAL);
		de = devfs_parent_dirent(dd);
		if (de == NULL)
			return (ENOENT);
		dvplocked = VOP_ISLOCKED(dvp);
		VOP_UNLOCK(dvp, 0);
		error = devfs_allocv(de, mp, cnp->cn_lkflags & LK_TYPE_MASK,
		    vpp);
		*dm_unlock = 0;
		vn_lock(dvp, dvplocked | LK_RETRY);
		return (error);
	}

	dd = dvp->v_data;
	de = devfs_find(dd, cnp->cn_nameptr, cnp->cn_namelen, 0);
	while (de == NULL) {	/* While(...) so we can use break */

		if (nameiop == DELETE)
			return (ENOENT);

		/*
		 * OK, we didn't have an entry for the name we were asked for
		 * so we try to see if anybody can create it on demand.
		 */
		pname = devfs_fqpn(specname, dmp, dd, cnp);
		if (pname == NULL)
			break;

		cdev = NULL;
		DEVFS_DMP_HOLD(dmp);
		sx_xunlock(&dmp->dm_lock);
		sx_slock(&clone_drain_lock);
		EVENTHANDLER_INVOKE(dev_clone,
		    td->td_ucred, pname, strlen(pname), &cdev);
		sx_sunlock(&clone_drain_lock);

		if (cdev == NULL)
			sx_xlock(&dmp->dm_lock);
		else if (devfs_populate_vp(dvp) != 0) {
			*dm_unlock = 0;
			sx_xlock(&dmp->dm_lock);
			if (DEVFS_DMP_DROP(dmp)) {
				sx_xunlock(&dmp->dm_lock);
				devfs_unmount_final(dmp);
			} else
				sx_xunlock(&dmp->dm_lock);
			dev_rel(cdev);
			return (ENOENT);
		}
		if (DEVFS_DMP_DROP(dmp)) {
			*dm_unlock = 0;
			sx_xunlock(&dmp->dm_lock);
			devfs_unmount_final(dmp);
			if (cdev != NULL)
				dev_rel(cdev);
			return (ENOENT);
		}

		if (cdev == NULL)
			break;

		dev_lock();
		dde = &cdev2priv(cdev)->cdp_dirents[dmp->dm_idx];
		if (dde != NULL && *dde != NULL)
			de = *dde;
		dev_unlock();
		dev_rel(cdev);
		break;
	}

	if (de == NULL || de->de_flags & DE_WHITEOUT) {
		if ((nameiop == CREATE || nameiop == RENAME) &&
		    (flags & (LOCKPARENT | WANTPARENT)) && (flags & ISLASTCN)) {
			cnp->cn_flags |= SAVENAME;
			return (EJUSTRETURN);
		}
		return (ENOENT);
	}

	if (devfs_prison_check(de, td))
		return (ENOENT);

	if ((cnp->cn_nameiop == DELETE) && (flags & ISLASTCN)) {
		error = VOP_ACCESS(dvp, VWRITE, cnp->cn_cred, td);
		if (error)
			return (error);
		if (*vpp == dvp) {
			VREF(dvp);
			*vpp = dvp;
			return (0);
		}
	}
	error = devfs_allocv(de, mp, cnp->cn_lkflags & LK_TYPE_MASK, vpp);
	*dm_unlock = 0;
	return (error);
}