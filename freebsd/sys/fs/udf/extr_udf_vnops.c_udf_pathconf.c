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
struct TYPE_2__ {int /*<<< orphan*/  v_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAXPATHLEN ; 
 int NAME_MAX ; 
 int PIPE_BUF ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VFIFO ; 
#define  _PC_FILESIZEBITS 133 
#define  _PC_LINK_MAX 132 
#define  _PC_NAME_MAX 131 
#define  _PC_NO_TRUNC 130 
#define  _PC_PIPE_BUF 129 
#define  _PC_SYMLINK_MAX 128 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 

__attribute__((used)) static int
udf_pathconf(struct vop_pathconf_args *a)
{

	switch (a->a_name) {
	case _PC_FILESIZEBITS:
		*a->a_retval = 64;
		return (0);
	case _PC_LINK_MAX:
		*a->a_retval = 65535;
		return (0);
	case _PC_NAME_MAX:
		*a->a_retval = NAME_MAX;
		return (0);
	case _PC_SYMLINK_MAX:
		*a->a_retval = MAXPATHLEN;
		return (0);
	case _PC_NO_TRUNC:
		*a->a_retval = 1;
		return (0);
	case _PC_PIPE_BUF:
		if (a->a_vp->v_type == VDIR || a->a_vp->v_type == VFIFO) {
			*a->a_retval = PIPE_BUF;
			return (0);
		}
		return (EINVAL);
	default:
		return (vop_stdpathconf(a));
	}
}