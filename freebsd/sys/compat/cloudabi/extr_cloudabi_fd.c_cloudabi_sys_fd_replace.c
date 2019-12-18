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
struct thread {scalar_t__* td_retval; } ;
struct cloudabi_sys_fd_replace_args {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDDUP_MUSTREPLACE ; 
 int kern_dup (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_fd_replace(struct thread *td,
    struct cloudabi_sys_fd_replace_args *uap)
{
	int error;

	/*
	 * CloudABI's equivalent to dup2(). CloudABI processes should
	 * not depend on hardcoded file descriptor layouts, but simply
	 * use the file descriptor numbers that are allocated by the
	 * kernel. Duplicating file descriptors to arbitrary numbers
	 * should not be done.
	 *
	 * Invoke kern_dup() with FDDUP_MUSTREPLACE, so that we return
	 * EBADF when duplicating to a nonexistent file descriptor. Also
	 * clear the return value, as this system call yields no return
	 * value.
	 */
	error = kern_dup(td, FDDUP_MUSTREPLACE, 0, uap->from, uap->to);
	td->td_retval[0] = 0;
	return (error);
}