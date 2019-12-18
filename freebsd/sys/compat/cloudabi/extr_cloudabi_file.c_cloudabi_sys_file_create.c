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
struct thread {int dummy; } ;
struct cloudabi_sys_file_create_args {int type; int /*<<< orphan*/  fd; int /*<<< orphan*/  path_len; int /*<<< orphan*/  path; } ;

/* Variables and functions */
#define  CLOUDABI_FILETYPE_DIRECTORY 128 
 int EINVAL ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  cloudabi_freestr (char*) ; 
 int copyin_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int kern_mkdirat (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int
cloudabi_sys_file_create(struct thread *td,
    struct cloudabi_sys_file_create_args *uap)
{
	char *path;
	int error;

	error = copyin_path(uap->path, uap->path_len, &path);
	if (error != 0)
		return (error);

	/*
	 * CloudABI processes cannot interact with UNIX credentials and
	 * permissions. Depend on the umask that is set prior to
	 * execution to restrict the file permissions.
	 */
	switch (uap->type) {
	case CLOUDABI_FILETYPE_DIRECTORY:
		error = kern_mkdirat(td, uap->fd, path, UIO_SYSSPACE, 0777);
		break;
	default:
		error = EINVAL;
		break;
	}
	cloudabi_freestr(path);
	return (error);
}