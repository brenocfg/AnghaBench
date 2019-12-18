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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {struct devfs_dirent* v_data; } ;
struct devfs_dirent {int /*<<< orphan*/ * de_vnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfs_de_interlock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devfs_reclaim(struct vop_reclaim_args *ap)
{
	struct vnode *vp;
	struct devfs_dirent *de;

	vp = ap->a_vp;
	mtx_lock(&devfs_de_interlock);
	de = vp->v_data;
	if (de != NULL) {
		de->de_vnode = NULL;
		vp->v_data = NULL;
	}
	mtx_unlock(&devfs_de_interlock);
	return (0);
}