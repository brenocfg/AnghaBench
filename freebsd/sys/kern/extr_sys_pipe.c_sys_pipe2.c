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
struct pipe2_args {int flags; int /*<<< orphan*/  fildes; } ;

/* Variables and functions */
 int EINVAL ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kern_close (struct thread*,int) ; 
 int kern_pipe (struct thread*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
sys_pipe2(struct thread *td, struct pipe2_args *uap)
{
	int error, fildes[2];

	if (uap->flags & ~(O_CLOEXEC | O_NONBLOCK))
		return (EINVAL);
	error = kern_pipe(td, fildes, uap->flags, NULL, NULL);
	if (error)
		return (error);
	error = copyout(fildes, uap->fildes, 2 * sizeof(int));
	if (error) {
		(void)kern_close(td, fildes[0]);
		(void)kern_close(td, fildes[1]);
	}
	return (error);
}