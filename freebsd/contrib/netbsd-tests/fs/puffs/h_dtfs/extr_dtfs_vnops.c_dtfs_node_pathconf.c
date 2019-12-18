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
struct puffs_usermount {int dummy; } ;
typedef  int register_t ;
typedef  int /*<<< orphan*/  puffs_cookie_t ;

/* Variables and functions */
 int EINVAL ; 
 int LINK_MAX ; 
 int MAXPATHLEN ; 
 int NAME_MAX ; 
 int PATH_MAX ; 
 int PIPE_BUF ; 
#define  _PC_2_SYMLINKS 137 
#define  _PC_CHOWN_RESTRICTED 136 
#define  _PC_FILESIZEBITS 135 
#define  _PC_LINK_MAX 134 
#define  _PC_NAME_MAX 133 
#define  _PC_NO_TRUNC 132 
#define  _PC_PATH_MAX 131 
#define  _PC_PIPE_BUF 130 
#define  _PC_SYMLINK_MAX 129 
#define  _PC_SYNC_IO 128 

int
dtfs_node_pathconf(struct puffs_usermount *pu, puffs_cookie_t opc,
	int name, register_t *retval)
{

	switch (name) {
	case _PC_LINK_MAX:
		*retval = LINK_MAX;
		return 0;
	case _PC_NAME_MAX:
		*retval = NAME_MAX;
		return 0;
	case _PC_PATH_MAX:
		*retval = PATH_MAX;
		return 0;
	case _PC_PIPE_BUF:
		*retval = PIPE_BUF;
		return 0;
	case _PC_CHOWN_RESTRICTED:
		*retval = 1;
		return 0;
	case _PC_NO_TRUNC:
		*retval = 1;
		return 0;
	case _PC_SYNC_IO:
		*retval = 1;
		return 0;
	case _PC_FILESIZEBITS:
		*retval = 43; /* this one goes to 11 */
		return 0;
	case _PC_SYMLINK_MAX:
		*retval = MAXPATHLEN;
		return 0;
	case _PC_2_SYMLINKS:
		*retval = 1;
		return 0;
	default:
		return EINVAL;
	}
}