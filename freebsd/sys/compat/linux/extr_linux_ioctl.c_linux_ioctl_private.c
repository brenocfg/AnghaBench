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
struct linux_ioctl_args {int /*<<< orphan*/  fd; } ;
struct file {int f_type; } ;

/* Variables and functions */
 int DTYPE_SOCKET ; 
 int ENOIOCTL ; 
 int /*<<< orphan*/  cap_ioctl_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int linux_ioctl_socket (struct thread*,struct linux_ioctl_args*) ; 

__attribute__((used)) static int
linux_ioctl_private(struct thread *td, struct linux_ioctl_args *args)
{
	struct file *fp;
	int error, type;

	error = fget(td, args->fd, &cap_ioctl_rights, &fp);
	if (error != 0)
		return (error);
	type = fp->f_type;
	fdrop(fp, td);
	if (type == DTYPE_SOCKET)
		return (linux_ioctl_socket(td, args));
	return (ENOIOCTL);
}