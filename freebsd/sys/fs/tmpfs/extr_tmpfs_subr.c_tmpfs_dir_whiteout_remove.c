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
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct tmpfs_dirent {int /*<<< orphan*/ * td_node; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  VFS_TO_TMPFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP_TO_TMPFS_DIR (struct vnode*) ; 
 int /*<<< orphan*/  tmpfs_dir_detach (struct vnode*,struct tmpfs_dirent*) ; 
 struct tmpfs_dirent* tmpfs_dir_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct componentname*) ; 
 int /*<<< orphan*/  tmpfs_free_dirent (int /*<<< orphan*/ ,struct tmpfs_dirent*) ; 

void
tmpfs_dir_whiteout_remove(struct vnode *dvp, struct componentname *cnp)
{
	struct tmpfs_dirent *de;

	de = tmpfs_dir_lookup(VP_TO_TMPFS_DIR(dvp), NULL, cnp);
	MPASS(de != NULL && de->td_node == NULL);
	tmpfs_dir_detach(dvp, de);
	tmpfs_free_dirent(VFS_TO_TMPFS(dvp->v_mount), de);
}