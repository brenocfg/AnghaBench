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
struct stat {int dummy; } ;
struct linux_newfstat_args {int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int kern_fstat (struct thread*,int /*<<< orphan*/ ,struct stat*) ; 
 int newstat_copyout (struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translate_fd_major_minor (struct thread*,int /*<<< orphan*/ ,struct stat*) ; 

int
linux_newfstat(struct thread *td, struct linux_newfstat_args *args)
{
	struct stat buf;
	int error;

	error = kern_fstat(td, args->fd, &buf);
	translate_fd_major_minor(td, args->fd, &buf);
	if (!error)
		error = newstat_copyout(&buf, args->buf);

	return (error);
}