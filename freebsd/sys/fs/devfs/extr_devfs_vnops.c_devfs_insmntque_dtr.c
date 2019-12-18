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
struct vnode {int /*<<< orphan*/ * v_data; } ;
struct devfs_dirent {int /*<<< orphan*/ * de_vnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfs_de_interlock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static void
devfs_insmntque_dtr(struct vnode *vp, void *arg)
{
	struct devfs_dirent *de;

	de = (struct devfs_dirent *)arg;
	mtx_lock(&devfs_de_interlock);
	vp->v_data = NULL;
	de->de_vnode = NULL;
	mtx_unlock(&devfs_de_interlock);
	vgone(vp);
	vput(vp);
}