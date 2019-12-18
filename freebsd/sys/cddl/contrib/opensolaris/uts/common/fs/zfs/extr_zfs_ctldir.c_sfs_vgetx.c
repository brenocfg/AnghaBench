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
typedef  int /*<<< orphan*/  uint64_t ;
struct vop_vector {int dummy; } ;
struct vnode {int /*<<< orphan*/ * v_data; int /*<<< orphan*/  v_vnlock; } ;
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  (* sfs_vnode_setup_fn ) (struct vnode*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT_IMPLY (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int getnewvnode (char const*,struct mount*,struct vop_vector*,struct vnode**) ; 
 int insmntque (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sfs_vnode_get (struct mount*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**) ; 
 int sfs_vnode_insert (struct vnode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**) ; 

__attribute__((used)) static int
sfs_vgetx(struct mount *mp, int flags, uint64_t parent_id, uint64_t id,
    const char *tag, struct vop_vector *vops,
    sfs_vnode_setup_fn setup, void *arg,
    struct vnode **vpp)
{
	struct vnode *vp;
	int error;

	error = sfs_vnode_get(mp, flags, parent_id, id, vpp);
	if (error != 0 || *vpp != NULL) {
		KASSERT_IMPLY(error == 0, (*vpp)->v_data != NULL,
		    "sfs vnode with no data");
		return (error);
	}

	/* Allocate a new vnode/inode. */
	error = getnewvnode(tag, mp, vops, &vp);
	if (error != 0) {
		*vpp = NULL;
		return (error);
	}

	/*
	 * Exclusively lock the vnode vnode while it's being constructed.
	 */
	lockmgr(vp->v_vnlock, LK_EXCLUSIVE, NULL);
	error = insmntque(vp, mp);
	if (error != 0) {
		*vpp = NULL;
		return (error);
	}

	setup(vp, arg);

	error = sfs_vnode_insert(vp, flags, parent_id, id, vpp);
	if (error != 0 || *vpp != NULL) {
		KASSERT_IMPLY(error == 0, (*vpp)->v_data != NULL,
		    "sfs vnode with no data");
		return (error);
	}

	*vpp = vp;
	return (0);
}