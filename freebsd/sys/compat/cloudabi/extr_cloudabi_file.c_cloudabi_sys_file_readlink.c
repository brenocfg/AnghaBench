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
struct cloudabi_sys_file_readlink_args {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; int /*<<< orphan*/  path_len; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  cloudabi_freestr (char*) ; 
 int copyin_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int kern_readlinkat (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_file_readlink(struct thread *td,
    struct cloudabi_sys_file_readlink_args *uap)
{
	char *path;
	int error;

	error = copyin_path(uap->path, uap->path_len, &path);
	if (error != 0)
		return (error);

	error = kern_readlinkat(td, uap->fd, path, UIO_SYSSPACE,
	    uap->buf, UIO_USERSPACE, uap->buf_len);
	cloudabi_freestr(path);
	return (error);
}