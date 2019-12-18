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
struct vnode {scalar_t__ v_type; int /*<<< orphan*/ * v_rdev; } ;
struct stat {int st_rdev; } ;

/* Variables and functions */
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  devtoname (int /*<<< orphan*/ *) ; 
 scalar_t__ linux_driver_get_major_minor (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
translate_vnhook_major_minor(struct vnode *vp, struct stat *sb)
{
	int major, minor;

	if (vp->v_type == VCHR && vp->v_rdev != NULL &&
	    linux_driver_get_major_minor(devtoname(vp->v_rdev),
	    &major, &minor) == 0) {
		sb->st_rdev = (major << 8 | minor);
	}
}