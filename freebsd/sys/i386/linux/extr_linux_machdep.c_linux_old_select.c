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
struct linux_select_args {int /*<<< orphan*/  timeout; int /*<<< orphan*/  exceptfds; int /*<<< orphan*/  writefds; int /*<<< orphan*/  readfds; int /*<<< orphan*/  nfds; } ;
struct linux_old_select_args {int /*<<< orphan*/  ptr; } ;
struct l_old_select_argv {int /*<<< orphan*/  timeout; int /*<<< orphan*/  exceptfds; int /*<<< orphan*/  writefds; int /*<<< orphan*/  readfds; int /*<<< orphan*/  nfds; } ;
typedef  int /*<<< orphan*/  linux_args ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ ,struct l_old_select_argv*,int) ; 
 int linux_select (struct thread*,struct linux_select_args*) ; 

int
linux_old_select(struct thread *td, struct linux_old_select_args *args)
{
	struct l_old_select_argv linux_args;
	struct linux_select_args newsel;
	int error;

	error = copyin(args->ptr, &linux_args, sizeof(linux_args));
	if (error)
		return (error);

	newsel.nfds = linux_args.nfds;
	newsel.readfds = linux_args.readfds;
	newsel.writefds = linux_args.writefds;
	newsel.exceptfds = linux_args.exceptfds;
	newsel.timeout = linux_args.timeout;
	return (linux_select(td, &newsel));
}