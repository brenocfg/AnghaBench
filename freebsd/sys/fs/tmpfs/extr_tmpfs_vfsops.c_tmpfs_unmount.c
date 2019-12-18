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
struct tmpfs_node {scalar_t__ tn_type; } ;
struct tmpfs_mount {int /*<<< orphan*/  tm_nodes_used; } ;
struct mount {scalar_t__ mnt_nvnodelistsize; int /*<<< orphan*/  mnt_flag; int /*<<< orphan*/ * mnt_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int FORCECLOSE ; 
 struct tmpfs_node* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_LOCAL ; 
 int /*<<< orphan*/  TMPFS_LOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 scalar_t__ VDIR ; 
 struct tmpfs_mount* VFS_TO_TMPFS (struct mount*) ; 
 int /*<<< orphan*/  VR_START_WRITE ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  tmpfs_dir_destroy (struct tmpfs_mount*,struct tmpfs_node*) ; 
 scalar_t__ tmpfs_free_node_locked (struct tmpfs_mount*,struct tmpfs_node*,int) ; 
 int /*<<< orphan*/  tmpfs_free_tmp (struct tmpfs_mount*) ; 
 int vflush (struct mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_write_resume (struct mount*,int /*<<< orphan*/ ) ; 
 int vfs_write_suspend_umnt (struct mount*) ; 

__attribute__((used)) static int
tmpfs_unmount(struct mount *mp, int mntflags)
{
	struct tmpfs_mount *tmp;
	struct tmpfs_node *node;
	int error, flags;

	flags = (mntflags & MNT_FORCE) != 0 ? FORCECLOSE : 0;
	tmp = VFS_TO_TMPFS(mp);

	/* Stop writers */
	error = vfs_write_suspend_umnt(mp);
	if (error != 0)
		return (error);
	/*
	 * At this point, nodes cannot be destroyed by any other
	 * thread because write suspension is started.
	 */

	for (;;) {
		error = vflush(mp, 0, flags, curthread);
		if (error != 0) {
			vfs_write_resume(mp, VR_START_WRITE);
			return (error);
		}
		MNT_ILOCK(mp);
		if (mp->mnt_nvnodelistsize == 0) {
			MNT_IUNLOCK(mp);
			break;
		}
		MNT_IUNLOCK(mp);
		if ((mntflags & MNT_FORCE) == 0) {
			vfs_write_resume(mp, VR_START_WRITE);
			return (EBUSY);
		}
	}

	TMPFS_LOCK(tmp);
	while ((node = LIST_FIRST(&tmp->tm_nodes_used)) != NULL) {
		TMPFS_NODE_LOCK(node);
		if (node->tn_type == VDIR)
			tmpfs_dir_destroy(tmp, node);
		if (tmpfs_free_node_locked(tmp, node, true))
			TMPFS_LOCK(tmp);
		else
			TMPFS_NODE_UNLOCK(node);
	}

	mp->mnt_data = NULL;
	tmpfs_free_tmp(tmp);
	vfs_write_resume(mp, VR_START_WRITE);

	MNT_ILOCK(mp);
	mp->mnt_flag &= ~MNT_LOCAL;
	MNT_IUNLOCK(mp);

	return (0);
}