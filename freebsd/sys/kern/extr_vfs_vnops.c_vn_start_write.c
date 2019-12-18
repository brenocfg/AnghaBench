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
struct vnode {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VOP_GETWRITEMOUNT (struct vnode*,struct mount**) ; 
 int V_MNTREF ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int vn_start_write_refed (struct mount*,int,int) ; 
 int /*<<< orphan*/  vn_suspendable (struct mount*) ; 

int
vn_start_write(struct vnode *vp, struct mount **mpp, int flags)
{
	struct mount *mp;
	int error;

	KASSERT((flags & V_MNTREF) == 0 || (*mpp != NULL && vp == NULL),
	    ("V_MNTREF requires mp"));

	error = 0;
	/*
	 * If a vnode is provided, get and return the mount point that
	 * to which it will write.
	 */
	if (vp != NULL) {
		if ((error = VOP_GETWRITEMOUNT(vp, mpp)) != 0) {
			*mpp = NULL;
			if (error != EOPNOTSUPP)
				return (error);
			return (0);
		}
	}
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
	if (vp == NULL && (flags & V_MNTREF) == 0)
		vfs_ref(mp);

	return (vn_start_write_refed(mp, flags, false));
}