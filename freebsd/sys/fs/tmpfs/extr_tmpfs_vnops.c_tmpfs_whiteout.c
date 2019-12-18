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
struct vop_whiteout_args {int a_flags; struct componentname* a_cnp; struct vnode* a_dvp; } ;
struct vnode {int dummy; } ;
struct tmpfs_dirent {int /*<<< orphan*/ * td_node; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
#define  CREATE 130 
#define  DELETE 129 
 int EEXIST ; 
#define  LOOKUP 128 
 int /*<<< orphan*/  VP_TO_TMPFS_DIR (struct vnode*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct tmpfs_dirent* tmpfs_dir_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct componentname*) ; 
 int tmpfs_dir_whiteout_add (struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  tmpfs_dir_whiteout_remove (struct vnode*,struct componentname*) ; 

__attribute__((used)) static int
tmpfs_whiteout(struct vop_whiteout_args *ap)
{
	struct vnode *dvp = ap->a_dvp;
	struct componentname *cnp = ap->a_cnp;
	struct tmpfs_dirent *de;

	switch (ap->a_flags) {
	case LOOKUP:
		return (0);
	case CREATE:
		de = tmpfs_dir_lookup(VP_TO_TMPFS_DIR(dvp), NULL, cnp);
		if (de != NULL)
			return (de->td_node == NULL ? 0 : EEXIST);
		return (tmpfs_dir_whiteout_add(dvp, cnp));
	case DELETE:
		tmpfs_dir_whiteout_remove(dvp, cnp);
		return (0);
	default:
		panic("tmpfs_whiteout: unknown op");
	}
}