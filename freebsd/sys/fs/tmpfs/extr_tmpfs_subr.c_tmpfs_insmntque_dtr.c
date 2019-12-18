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
struct vnode {int /*<<< orphan*/ * v_op; int /*<<< orphan*/ * v_data; int /*<<< orphan*/ * v_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  dead_vnodeops ; 
 int /*<<< orphan*/  tmpfs_destroy_vobject (struct vnode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static void
tmpfs_insmntque_dtr(struct vnode *vp, void *dtr_arg)
{

	tmpfs_destroy_vobject(vp, vp->v_object);
	vp->v_object = NULL;
	vp->v_data = NULL;
	vp->v_op = &dead_vnodeops;
	vgone(vp);
	vput(vp);
}