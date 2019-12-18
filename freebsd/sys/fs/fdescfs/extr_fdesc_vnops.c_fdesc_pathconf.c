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
struct vop_pathconf_args {int a_name; int* a_retval; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd_fd; int /*<<< orphan*/  fd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  Froot ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int NAME_MAX ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* VTOFDESC (struct vnode*) ; 
#define  _PC_LINK_MAX 129 
#define  _PC_NAME_MAX 128 
 int /*<<< orphan*/  curthread ; 
 int kern_fpathconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 
 int /*<<< orphan*/  vunref (struct vnode*) ; 

__attribute__((used)) static int
fdesc_pathconf(struct vop_pathconf_args *ap)
{
	struct vnode *vp = ap->a_vp;
	int error;

	switch (ap->a_name) {
	case _PC_NAME_MAX:
		*ap->a_retval = NAME_MAX;
		return (0);
	case _PC_LINK_MAX:
		if (VTOFDESC(vp)->fd_type == Froot)
			*ap->a_retval = 2;
		else
			*ap->a_retval = 1;
		return (0);
	default:
		if (VTOFDESC(vp)->fd_type == Froot)
			return (vop_stdpathconf(ap));
		vref(vp);
		VOP_UNLOCK(vp, 0);
		error = kern_fpathconf(curthread, VTOFDESC(vp)->fd_fd,
		    ap->a_name, ap->a_retval);
		vn_lock(vp, LK_SHARED | LK_RETRY);
		vunref(vp);
		return (error);
	}
}