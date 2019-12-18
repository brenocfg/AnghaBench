#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  v_mount; struct mount* v_mountedhere; TYPE_2__* v_data; } ;
typedef  TYPE_1__ vnode_t ;
struct vop_vptocnp_args {size_t* a_buflen; scalar_t__ a_buf; TYPE_1__** a_vpp; TYPE_1__* a_vp; } ;
struct mount {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  sn_name; } ;
typedef  TYPE_2__ sfs_node_t ;
typedef  enum vgetstate { ____Placeholder_vgetstate } vgetstate ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int VOP_ISLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vget_finish (TYPE_1__*,int,int) ; 
 int vget_prep (TYPE_1__*) ; 
 int /*<<< orphan*/  vput (TYPE_1__*) ; 
 int zfsctl_snapdir_vnode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static int
zfsctl_snapshot_vptocnp(struct vop_vptocnp_args *ap)
{
	struct mount *mp;
	vnode_t *dvp;
	vnode_t *vp;
	sfs_node_t *node;
	size_t len;
	enum vgetstate vs;
	int locked;
	int error;

	vp = ap->a_vp;
	node = vp->v_data;
	len = strlen(node->sn_name);
	if (*ap->a_buflen < len)
		return (SET_ERROR(ENOMEM));

	/*
	 * Prevent unmounting of the snapshot while the vnode lock
	 * is not held.  That is not strictly required, but allows
	 * us to assert that an uncovered snapshot vnode is never
	 * "leaked".
	 */
	mp = vp->v_mountedhere;
	if (mp == NULL)
		return (SET_ERROR(ENOENT));
	error = vfs_busy(mp, 0);
	KASSERT(error == 0, ("vfs_busy(mp, 0) failed with %d", error));

	/*
	 * We can vput the vnode as we can now depend on the reference owned
	 * by the busied mp.  But we also need to hold the vnode, because
	 * the reference may go after vfs_unbusy() which has to be called
	 * before we can lock the vnode again.
	 */
	locked = VOP_ISLOCKED(vp);
	vs = vget_prep(vp);
	vput(vp);

	/* Look up .zfs/snapshot, our parent. */
	error = zfsctl_snapdir_vnode(vp->v_mount, NULL, LK_SHARED, &dvp);
	if (error == 0) {
		VOP_UNLOCK(dvp, 0);
		*ap->a_vpp = dvp;
		*ap->a_buflen -= len;
		bcopy(node->sn_name, ap->a_buf + *ap->a_buflen, len);
	}
	vfs_unbusy(mp);
	vget_finish(vp, locked | LK_RETRY, vs);
	return (error);
}