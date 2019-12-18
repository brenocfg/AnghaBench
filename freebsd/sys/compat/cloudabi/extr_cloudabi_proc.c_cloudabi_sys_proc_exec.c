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
struct cloudabi_sys_proc_exec_args {int /*<<< orphan*/  fd; int /*<<< orphan*/  fds_len; int /*<<< orphan*/  fds; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int exec_copyin_data_fds (struct thread*,struct image_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_execve (struct thread*,struct image_args*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_execve (struct thread*,int,struct vmspace*) ; 
 int pre_execve (struct thread*,struct vmspace**) ; 

int
cloudabi_sys_proc_exec(struct thread *td,
    struct cloudabi_sys_proc_exec_args *uap)
{
	struct image_args args;
	struct vmspace *oldvmspace;
	int error;

	error = pre_execve(td, &oldvmspace);
	if (error != 0)
		return (error);
	error = exec_copyin_data_fds(td, &args, uap->data, uap->data_len,
	    uap->fds, uap->fds_len);
	if (error == 0) {
		args.fd = uap->fd;
		error = kern_execve(td, &args, NULL);
	}
	post_execve(td, error, oldvmspace);
	return (error);
}