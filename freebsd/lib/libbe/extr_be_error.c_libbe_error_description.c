#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int error; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
#define  BE_ERR_BADMOUNT 147 
#define  BE_ERR_BADPATH 146 
#define  BE_ERR_DESTROYACT 145 
#define  BE_ERR_DESTROYMNT 144 
#define  BE_ERR_EXISTS 143 
#define  BE_ERR_INVALIDNAME 142 
#define  BE_ERR_INVORIGIN 141 
#define  BE_ERR_IO 140 
#define  BE_ERR_MOUNTED 139 
#define  BE_ERR_NOENT 138 
#define  BE_ERR_NOMEM 137 
#define  BE_ERR_NOMOUNT 136 
#define  BE_ERR_NOORIGIN 135 
#define  BE_ERR_NOPOOL 134 
#define  BE_ERR_PATHBUSY 133 
#define  BE_ERR_PATHLEN 132 
#define  BE_ERR_PERMS 131 
 int BE_ERR_SUCCESS ; 
#define  BE_ERR_UNKNOWN 130 
#define  BE_ERR_ZFSCLONE 129 
#define  BE_ERR_ZFSOPEN 128 
 int /*<<< orphan*/  assert (int) ; 

const char *
libbe_error_description(libbe_handle_t *lbh)
{

	switch (lbh->error) {
	case BE_ERR_INVALIDNAME:
		return ("invalid boot environment name");

	case BE_ERR_EXISTS:
		return ("boot environment name already taken");

	case BE_ERR_NOENT:
		return ("specified boot environment does not exist");

	case BE_ERR_PERMS:
		return ("insufficient permissions");

	case BE_ERR_DESTROYACT:
		return ("cannot destroy active boot environment");

	case BE_ERR_DESTROYMNT:
		return ("cannot destroy mounted boot env unless forced");

	case BE_ERR_BADPATH:
		return ("path not suitable for operation");

	case BE_ERR_PATHBUSY:
		return ("specified path is busy");

	case BE_ERR_PATHLEN:
		return ("provided path name exceeds maximum length limit");

	case BE_ERR_BADMOUNT:
		return ("mountpoint is not \"/\"");

	case BE_ERR_NOORIGIN:
		return ("could not open snapshot's origin");

	case BE_ERR_MOUNTED:
		return ("boot environment is already mounted");

	case BE_ERR_NOMOUNT:
		return ("boot environment is not mounted");

	case BE_ERR_ZFSOPEN:
		return ("calling zfs_open() failed");

	case BE_ERR_ZFSCLONE:
		return ("error when calling zfs_clone() to create boot env");

	case BE_ERR_IO:
		return ("input/output error");

	case BE_ERR_NOPOOL:
		return ("operation not supported on this pool");

	case BE_ERR_NOMEM:
		return ("insufficient memory");

	case BE_ERR_UNKNOWN:
		return ("unknown error");

	case BE_ERR_INVORIGIN:
		return ("invalid origin");

	default:
		assert(lbh->error == BE_ERR_SUCCESS);
		return ("no error");
	}
}