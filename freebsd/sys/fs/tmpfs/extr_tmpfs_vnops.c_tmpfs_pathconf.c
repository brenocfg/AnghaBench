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
struct vop_pathconf_args {int a_name; long* a_retval; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_type; } ;

/* Variables and functions */
 int EINVAL ; 
 long NAME_MAX ; 
 long PIPE_BUF ; 
 long TMPFS_LINK_MAX ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VFIFO ; 
#define  _PC_CHOWN_RESTRICTED 134 
#define  _PC_FILESIZEBITS 133 
#define  _PC_LINK_MAX 132 
#define  _PC_NAME_MAX 131 
#define  _PC_NO_TRUNC 130 
#define  _PC_PIPE_BUF 129 
#define  _PC_SYNC_IO 128 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 

int
tmpfs_pathconf(struct vop_pathconf_args *v)
{
	struct vnode *vp = v->a_vp;
	int name = v->a_name;
	long *retval = v->a_retval;

	int error;

	error = 0;

	switch (name) {
	case _PC_LINK_MAX:
		*retval = TMPFS_LINK_MAX;
		break;

	case _PC_NAME_MAX:
		*retval = NAME_MAX;
		break;

	case _PC_PIPE_BUF:
		if (vp->v_type == VDIR || vp->v_type == VFIFO)
			*retval = PIPE_BUF;
		else
			error = EINVAL;
		break;

	case _PC_CHOWN_RESTRICTED:
		*retval = 1;
		break;

	case _PC_NO_TRUNC:
		*retval = 1;
		break;

	case _PC_SYNC_IO:
		*retval = 1;
		break;

	case _PC_FILESIZEBITS:
		*retval = 64;
		break;

	default:
		error = vop_stdpathconf(v);
	}

	return error;
}