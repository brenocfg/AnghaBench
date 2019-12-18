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
struct vop_pathconf_args {int a_name; int* a_retval; TYPE_1__* a_vp; } ;
struct TYPE_2__ {int v_vflag; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
 int MAXPATHLEN ; 
 int MAX_CANON ; 
 int MAX_INPUT ; 
 int NAME_MAX ; 
 int VV_ISTTY ; 
#define  _PC_CHOWN_RESTRICTED 136 
#define  _PC_FILESIZEBITS 135 
#define  _PC_LINK_MAX 134 
#define  _PC_MAC_PRESENT 133 
#define  _PC_MAX_CANON 132 
#define  _PC_MAX_INPUT 131 
#define  _PC_NAME_MAX 130 
#define  _PC_SYMLINK_MAX 129 
#define  _PC_VDISABLE 128 
 int _POSIX_VDISABLE ; 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 

__attribute__((used)) static int
devfs_pathconf(struct vop_pathconf_args *ap)
{

	switch (ap->a_name) {
	case _PC_FILESIZEBITS:
		*ap->a_retval = 64;
		return (0);
	case _PC_NAME_MAX:
		*ap->a_retval = NAME_MAX;
		return (0);
	case _PC_LINK_MAX:
		*ap->a_retval = INT_MAX;
		return (0);
	case _PC_SYMLINK_MAX:
		*ap->a_retval = MAXPATHLEN;
		return (0);
	case _PC_MAX_CANON:
		if (ap->a_vp->v_vflag & VV_ISTTY) {
			*ap->a_retval = MAX_CANON;
			return (0);
		}
		return (EINVAL);
	case _PC_MAX_INPUT:
		if (ap->a_vp->v_vflag & VV_ISTTY) {
			*ap->a_retval = MAX_INPUT;
			return (0);
		}
		return (EINVAL);
	case _PC_VDISABLE:
		if (ap->a_vp->v_vflag & VV_ISTTY) {
			*ap->a_retval = _POSIX_VDISABLE;
			return (0);
		}
		return (EINVAL);
	case _PC_MAC_PRESENT:
#ifdef MAC
		/*
		 * If MAC is enabled, devfs automatically supports
		 * trivial non-persistant label storage.
		 */
		*ap->a_retval = 1;
#else
		*ap->a_retval = 0;
#endif
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	default:
		return (vop_stdpathconf(ap));
	}
	/* NOTREACHED */
}