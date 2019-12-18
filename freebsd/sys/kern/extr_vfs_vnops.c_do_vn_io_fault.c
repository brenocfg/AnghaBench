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
struct vnode {scalar_t__ v_type; struct mount* v_mount; } ;
struct uio {scalar_t__ uio_segflg; } ;
struct mount {int mnt_kern_flag; } ;

/* Variables and functions */
 int MNTK_NO_IOPF ; 
 scalar_t__ UIO_USERSPACE ; 
 scalar_t__ VREG ; 
 scalar_t__ vn_io_fault_enable ; 

__attribute__((used)) static bool
do_vn_io_fault(struct vnode *vp, struct uio *uio)
{
	struct mount *mp;

	return (uio->uio_segflg == UIO_USERSPACE && vp->v_type == VREG &&
	    (mp = vp->v_mount) != NULL &&
	    (mp->mnt_kern_flag & MNTK_NO_IOPF) != 0 && vn_io_fault_enable);
}