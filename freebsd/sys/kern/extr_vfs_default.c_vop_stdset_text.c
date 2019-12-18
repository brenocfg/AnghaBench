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
struct vop_set_text_args {struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_writecount; int /*<<< orphan*/  v_iflag; struct mount* v_mount; } ;
struct mount {int mnt_kern_flag; } ;

/* Variables and functions */
 int ETXTBSY ; 
 int MNTK_TEXT_REFS ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_TEXT_REF ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  vrefl (struct vnode*) ; 

int
vop_stdset_text(struct vop_set_text_args *ap)
{
	struct vnode *vp;
	struct mount *mp;
	int error;

	vp = ap->a_vp;
	VI_LOCK(vp);
	if (vp->v_writecount > 0) {
		error = ETXTBSY;
	} else {
		/*
		 * If requested by fs, keep a use reference to the
		 * vnode until the last text reference is released.
		 */
		mp = vp->v_mount;
		if (mp != NULL && (mp->mnt_kern_flag & MNTK_TEXT_REFS) != 0 &&
		    vp->v_writecount == 0) {
			vp->v_iflag |= VI_TEXT_REF;
			vrefl(vp);
		}

		vp->v_writecount--;
		error = 0;
	}
	VI_UNLOCK(vp);
	return (error);
}