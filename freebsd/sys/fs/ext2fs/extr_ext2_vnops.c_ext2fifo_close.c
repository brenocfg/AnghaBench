#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vop_close_args {struct vnode* a_vp; } ;
struct vnode {int v_usecount; } ;
struct TYPE_2__ {int (* vop_close ) (struct vop_close_args*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  ext2_itimes_locked (struct vnode*) ; 
 TYPE_1__ fifo_specops ; 
 int stub1 (struct vop_close_args*) ; 

__attribute__((used)) static int
ext2fifo_close(struct vop_close_args *ap)
{
	struct vnode *vp = ap->a_vp;

	VI_LOCK(vp);
	if (vp->v_usecount > 1)
		ext2_itimes_locked(vp);
	VI_UNLOCK(vp);
	return (fifo_specops.vop_close(ap));
}