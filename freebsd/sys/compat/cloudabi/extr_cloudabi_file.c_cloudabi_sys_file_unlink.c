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
struct cloudabi_sys_file_unlink_args {int flags; int /*<<< orphan*/  fd; int /*<<< orphan*/  path_len; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int CLOUDABI_UNLINK_REMOVEDIR ; 
 int /*<<< orphan*/  FD_NONE ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  cloudabi_freestr (char*) ; 
 int copyin_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int kern_frmdirat (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_funlinkat (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_file_unlink(struct thread *td,
    struct cloudabi_sys_file_unlink_args *uap)
{
	char *path;
	int error;

	error = copyin_path(uap->path, uap->path_len, &path);
	if (error != 0)
		return (error);

	if (uap->flags & CLOUDABI_UNLINK_REMOVEDIR)
		error = kern_frmdirat(td, uap->fd, path, FD_NONE,
		    UIO_SYSSPACE, 0);
	else
		error = kern_funlinkat(td, uap->fd, path, FD_NONE,
		    UIO_SYSSPACE, 0, 0);
	cloudabi_freestr(path);
	return (error);
}