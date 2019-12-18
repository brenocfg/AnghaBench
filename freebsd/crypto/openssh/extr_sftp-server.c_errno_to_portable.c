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

/* Variables and functions */
#define  EACCES 137 
#define  EBADF 136 
#define  EFAULT 135 
#define  EINVAL 134 
#define  ELOOP 133 
#define  ENAMETOOLONG 132 
#define  ENOENT 131 
#define  ENOSYS 130 
#define  ENOTDIR 129 
#define  EPERM 128 
 int SSH2_FX_BAD_MESSAGE ; 
 int SSH2_FX_FAILURE ; 
 int SSH2_FX_NO_SUCH_FILE ; 
 int SSH2_FX_OK ; 
 int SSH2_FX_OP_UNSUPPORTED ; 
 int SSH2_FX_PERMISSION_DENIED ; 

__attribute__((used)) static int
errno_to_portable(int unixerrno)
{
	int ret = 0;

	switch (unixerrno) {
	case 0:
		ret = SSH2_FX_OK;
		break;
	case ENOENT:
	case ENOTDIR:
	case EBADF:
	case ELOOP:
		ret = SSH2_FX_NO_SUCH_FILE;
		break;
	case EPERM:
	case EACCES:
	case EFAULT:
		ret = SSH2_FX_PERMISSION_DENIED;
		break;
	case ENAMETOOLONG:
	case EINVAL:
		ret = SSH2_FX_BAD_MESSAGE;
		break;
	case ENOSYS:
		ret = SSH2_FX_OP_UNSUPPORTED;
		break;
	default:
		ret = SSH2_FX_FAILURE;
		break;
	}
	return ret;
}