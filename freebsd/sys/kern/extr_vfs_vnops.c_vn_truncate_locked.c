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
struct vnode {int dummy; } ;
struct vattr {int /*<<< orphan*/  va_vaflags; int /*<<< orphan*/  va_size; } ;
struct ucred {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  VATTR_NULL (struct vattr*) ; 
 int /*<<< orphan*/  VA_SYNC ; 
 int VOP_ADD_WRITECOUNT (struct vnode*,int) ; 
 int /*<<< orphan*/  VOP_ADD_WRITECOUNT_CHECKED (struct vnode*,int) ; 
 int VOP_SETATTR (struct vnode*,struct vattr*,struct ucred*) ; 

int
vn_truncate_locked(struct vnode *vp, off_t length, bool sync,
    struct ucred *cred)
{
	struct vattr vattr;
	int error;

	error = VOP_ADD_WRITECOUNT(vp, 1);
	if (error == 0) {
		VATTR_NULL(&vattr);
		vattr.va_size = length;
		if (sync)
			vattr.va_vaflags |= VA_SYNC;
		error = VOP_SETATTR(vp, &vattr, cred);
		VOP_ADD_WRITECOUNT_CHECKED(vp, -1);
	}
	return (error);
}