#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ u_quad_t ;
typedef  scalar_t__ u_long ;
struct vop_setattr_args {struct vattr* a_vap; struct vnode* a_vp; } ;
struct vnode {int v_type; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;
struct vattr {scalar_t__ va_flags; scalar_t__ va_uid; scalar_t__ va_gid; scalar_t__ va_mode; scalar_t__ va_size; TYPE_2__ va_mtime; TYPE_1__ va_atime; } ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int EISDIR ; 
 int EROFS ; 
#define  VBAD 137 
#define  VBLK 136 
#define  VCHR 135 
#define  VDIR 134 
#define  VFIFO 133 
#define  VLNK 132 
#define  VMARKER 131 
#define  VNON 130 
 scalar_t__ VNOVAL ; 
#define  VREG 129 
#define  VSOCK 128 

__attribute__((used)) static int
udf_setattr(struct vop_setattr_args *a)
{
	struct vnode *vp;
	struct vattr *vap;

	vp = a->a_vp;
	vap = a->a_vap;
	if (vap->va_flags != (u_long)VNOVAL || vap->va_uid != (uid_t)VNOVAL ||
	    vap->va_gid != (gid_t)VNOVAL || vap->va_atime.tv_sec != VNOVAL ||
	    vap->va_mtime.tv_sec != VNOVAL || vap->va_mode != (mode_t)VNOVAL)
		return (EROFS);
	if (vap->va_size != (u_quad_t)VNOVAL) {
		switch (vp->v_type) {
		case VDIR:
			return (EISDIR);
		case VLNK:
		case VREG:
			return (EROFS);
		case VCHR:
		case VBLK:
		case VSOCK:
		case VFIFO:
		case VNON:
		case VBAD:
		case VMARKER:
			return (0);
		}
	}
	return (0);
}