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
struct vop_pathconf_args {int a_name; int* a_retval; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_LINK_MAX ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int MAXPATHLEN ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAME_MAX ; 
#define  _PC_FILESIZEBITS 132 
#define  _PC_LINK_MAX 131 
#define  _PC_NAME_MAX 130 
#define  _PC_NO_TRUNC 129 
#define  _PC_SYMLINK_MAX 128 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 

__attribute__((used)) static int
fuse_vnop_pathconf(struct vop_pathconf_args *ap)
{

	switch (ap->a_name) {
	case _PC_FILESIZEBITS:
		*ap->a_retval = 64;
		return (0);
	case _PC_NAME_MAX:
		*ap->a_retval = NAME_MAX;
		return (0);
	case _PC_LINK_MAX:
		*ap->a_retval = MIN(LONG_MAX, FUSE_LINK_MAX);
		return (0);
	case _PC_SYMLINK_MAX:
		*ap->a_retval = MAXPATHLEN;
		return (0);
	case _PC_NO_TRUNC:
		*ap->a_retval = 1;
		return (0);
	default:
		return (vop_stdpathconf(ap));
	}
}