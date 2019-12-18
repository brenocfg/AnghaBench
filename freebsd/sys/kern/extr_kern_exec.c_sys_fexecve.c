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
struct vmspace {int dummy; } ;
struct thread {int dummy; } ;
struct image_args {int /*<<< orphan*/  fd; } ;
struct fexecve_args {int /*<<< orphan*/  fd; int /*<<< orphan*/  envv; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int exec_copyin_args (struct image_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_execve (struct thread*,struct image_args*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_execve (struct thread*,int,struct vmspace*) ; 
 int pre_execve (struct thread*,struct vmspace**) ; 

int
sys_fexecve(struct thread *td, struct fexecve_args *uap)
{
	struct image_args args;
	struct vmspace *oldvmspace;
	int error;

	error = pre_execve(td, &oldvmspace);
	if (error != 0)
		return (error);
	error = exec_copyin_args(&args, NULL, UIO_SYSSPACE,
	    uap->argv, uap->envv);
	if (error == 0) {
		args.fd = uap->fd;
		error = kern_execve(td, &args, NULL);
	}
	post_execve(td, error, oldvmspace);
	return (error);
}