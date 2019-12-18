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
struct linux_fallocate_args {scalar_t__ mode; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int ENOSYS ; 
 int kern_posix_fallocate (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_fallocate(struct thread *td, struct linux_fallocate_args *args)
{

	/*
	 * We emulate only posix_fallocate system call for which
	 * mode should be 0.
	 */
	if (args->mode != 0)
		return (ENOSYS);

	return (kern_posix_fallocate(td, args->fd, args->offset,
	    args->len));
}