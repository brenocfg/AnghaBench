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
struct vop_pathconf_args {int a_name; int* a_retval; int /*<<< orphan*/  a_vp; } ;
struct msdosfsmount {int pm_flags; } ;
struct TYPE_2__ {struct msdosfsmount* de_pmp; } ;

/* Variables and functions */
 int MSDOSFSMNT_LONGNAME ; 
 TYPE_1__* VTODE (int /*<<< orphan*/ ) ; 
 int WIN_MAXLEN ; 
#define  _PC_CHOWN_RESTRICTED 132 
#define  _PC_FILESIZEBITS 131 
#define  _PC_LINK_MAX 130 
#define  _PC_NAME_MAX 129 
#define  _PC_NO_TRUNC 128 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 

__attribute__((used)) static int
msdosfs_pathconf(struct vop_pathconf_args *ap)
{
	struct msdosfsmount *pmp = VTODE(ap->a_vp)->de_pmp;

	switch (ap->a_name) {
	case _PC_FILESIZEBITS:
		*ap->a_retval = 32;
		return (0);
	case _PC_LINK_MAX:
		*ap->a_retval = 1;
		return (0);
	case _PC_NAME_MAX:
		*ap->a_retval = pmp->pm_flags & MSDOSFSMNT_LONGNAME ? WIN_MAXLEN : 12;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	case _PC_NO_TRUNC:
		*ap->a_retval = 0;
		return (0);
	default:
		return (vop_stdpathconf(ap));
	}
	/* NOTREACHED */
}