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
typedef  scalar_t__ u_long ;
struct vnode {int /*<<< orphan*/  v_hash; int /*<<< orphan*/  v_mount; } ;
struct vfs_hash_head {int dummy; } ;

/* Variables and functions */
 struct vnode* LIST_FIRST (struct vfs_hash_head*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_VFS_HASH ; 
 int /*<<< orphan*/  free (struct vfs_hash_head*,int /*<<< orphan*/ ) ; 
 struct vfs_hash_head* hashinit (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_hashlist ; 
 int /*<<< orphan*/  vfs_hash_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_hash_lock ; 
 scalar_t__ vfs_hash_mask ; 
 struct vfs_hash_head* vfs_hash_tbl ; 

void
vfs_hash_changesize(int newmaxvnodes)
{
	struct vfs_hash_head *vfs_hash_newtbl, *vfs_hash_oldtbl;
	u_long vfs_hash_newmask, vfs_hash_oldmask;
	struct vnode *vp;
	int i;

	vfs_hash_newtbl = hashinit(newmaxvnodes, M_VFS_HASH,
		&vfs_hash_newmask);
	/* If same hash table size, nothing to do */
	if (vfs_hash_mask == vfs_hash_newmask) {
		free(vfs_hash_newtbl, M_VFS_HASH);
		return;
	}
	/*
	 * Move everything from the old hash table to the new table.
	 * None of the vnodes in the table can be recycled because to
	 * do so, they have to be removed from the hash table.
	 */
	rw_wlock(&vfs_hash_lock);
	vfs_hash_oldtbl = vfs_hash_tbl;
	vfs_hash_oldmask = vfs_hash_mask;
	vfs_hash_tbl = vfs_hash_newtbl;
	vfs_hash_mask = vfs_hash_newmask;
	for (i = 0; i <= vfs_hash_oldmask; i++) {
		while ((vp = LIST_FIRST(&vfs_hash_oldtbl[i])) != NULL) {
			LIST_REMOVE(vp, v_hashlist);
			LIST_INSERT_HEAD(
			    vfs_hash_bucket(vp->v_mount, vp->v_hash),
			    vp, v_hashlist);
		}
	}
	rw_wunlock(&vfs_hash_lock);
	free(vfs_hash_oldtbl, M_VFS_HASH);
}