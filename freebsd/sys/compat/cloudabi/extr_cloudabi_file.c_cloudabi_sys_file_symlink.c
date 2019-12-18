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
struct cloudabi_sys_file_symlink_args {int /*<<< orphan*/  fd; int /*<<< orphan*/  path2_len; int /*<<< orphan*/  path2; int /*<<< orphan*/  path1_len; int /*<<< orphan*/  path1; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  cloudabi_freestr (char*) ; 
 int copyin_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int kern_symlinkat (struct thread*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_file_symlink(struct thread *td,
    struct cloudabi_sys_file_symlink_args *uap)
{
	char *path1, *path2;
	int error;

	error = copyin_path(uap->path1, uap->path1_len, &path1);
	if (error != 0)
		return (error);
	error = copyin_path(uap->path2, uap->path2_len, &path2);
	if (error != 0) {
		cloudabi_freestr(path1);
		return (error);
	}

	error = kern_symlinkat(td, path1, uap->fd, path2, UIO_SYSSPACE);
	cloudabi_freestr(path1);
	cloudabi_freestr(path2);
	return (error);
}