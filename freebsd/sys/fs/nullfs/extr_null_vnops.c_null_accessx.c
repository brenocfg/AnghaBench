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
struct vop_generic_args {int dummy; } ;
struct vop_accessx_args {int a_accmode; struct vnode* a_vp; } ;
struct vnode {int v_type; TYPE_1__* v_mount; } ;
typedef  int accmode_t ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int EROFS ; 
 int MNT_RDONLY ; 
#define  VDIR 130 
#define  VLNK 129 
#define  VREG 128 
 int VWRITE ; 
 int null_bypass (struct vop_generic_args*) ; 

__attribute__((used)) static int
null_accessx(struct vop_accessx_args *ap)
{
	struct vnode *vp = ap->a_vp;
	accmode_t accmode = ap->a_accmode;

	/*
	 * Disallow write attempts on read-only layers;
	 * unless the file is a socket, fifo, or a block or
	 * character device resident on the filesystem.
	 */
	if (accmode & VWRITE) {
		switch (vp->v_type) {
		case VDIR:
		case VLNK:
		case VREG:
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
			break;
		default:
			break;
		}
	}
	return (null_bypass((struct vop_generic_args *)ap));
}