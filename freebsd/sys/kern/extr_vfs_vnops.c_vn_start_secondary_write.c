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
struct vnode {int dummy; } ;
struct mount {int mnt_kern_flag; TYPE_1__* mnt_vfc; int /*<<< orphan*/  mnt_flag; int /*<<< orphan*/  mnt_secondary_accwrites; int /*<<< orphan*/  mnt_secondary_writes; } ;
struct TYPE_2__ {int vfc_flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MNTK_SUSPEND2 ; 
 int MNTK_SUSPENDED ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_MTX (struct mount*) ; 
 int /*<<< orphan*/  MNT_REF (struct mount*) ; 
 int /*<<< orphan*/  MNT_REL (struct mount*) ; 
 int PCATCH ; 
 int PDROP ; 
 int PUSER ; 
 int VFCF_SBDRY ; 
 int VOP_GETWRITEMOUNT (struct vnode*,struct mount**) ; 
 int V_MNTREF ; 
 int V_NOWAIT ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int /*<<< orphan*/  vn_suspendable (struct mount*) ; 

int
vn_start_secondary_write(struct vnode *vp, struct mount **mpp, int flags)
{
	struct mount *mp;
	int error;

	KASSERT((flags & V_MNTREF) == 0 || (*mpp != NULL && vp == NULL),
	    ("V_MNTREF requires mp"));

 retry:
	if (vp != NULL) {
		if ((error = VOP_GETWRITEMOUNT(vp, mpp)) != 0) {
			*mpp = NULL;
			if (error != EOPNOTSUPP)
				return (error);
			return (0);
		}
	}
	/*
	 * If we are not suspended or have not yet reached suspended
	 * mode, then let the operation proceed.
	 */
	if ((mp = *mpp) == NULL)
		return (0);

	if (!vn_suspendable(mp)) {
		if (vp != NULL || (flags & V_MNTREF) != 0)
			vfs_rel(mp);
		return (0);
	}

	/*
	 * VOP_GETWRITEMOUNT() returns with the mp refcount held through
	 * a vfs_ref().
	 * As long as a vnode is not provided we need to acquire a
	 * refcount for the provided mountpoint too, in order to
	 * emulate a vfs_ref().
	 */
	MNT_ILOCK(mp);
	if (vp == NULL && (flags & V_MNTREF) == 0)
		MNT_REF(mp);
	if ((mp->mnt_kern_flag & (MNTK_SUSPENDED | MNTK_SUSPEND2)) == 0) {
		mp->mnt_secondary_writes++;
		mp->mnt_secondary_accwrites++;
		MNT_IUNLOCK(mp);
		return (0);
	}
	if (flags & V_NOWAIT) {
		MNT_REL(mp);
		MNT_IUNLOCK(mp);
		return (EWOULDBLOCK);
	}
	/*
	 * Wait for the suspension to finish.
	 */
	error = msleep(&mp->mnt_flag, MNT_MTX(mp), (PUSER - 1) | PDROP |
	    ((mp->mnt_vfc->vfc_flags & VFCF_SBDRY) != 0 ? (flags & PCATCH) : 0),
	    "suspfs", 0);
	vfs_rel(mp);
	if (error == 0)
		goto retry;
	return (error);
}