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
struct thread {int* td_retval; } ;
struct posix_openpt_args {int flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FFLAGS (int) ; 
 int O_ACCMODE ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_RDWR ; 
 int falloc (struct thread*,struct file**,int*,int) ; 
 int /*<<< orphan*/  fdclose (struct thread*,struct file*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int pts_alloc (int /*<<< orphan*/ ,struct thread*,struct file*) ; 

int
sys_posix_openpt(struct thread *td, struct posix_openpt_args *uap)
{
	int error, fd;
	struct file *fp;

	/*
	 * POSIX states it's unspecified when other flags are passed. We
	 * don't allow this.
	 */
	if (uap->flags & ~(O_RDWR|O_NOCTTY|O_CLOEXEC))
		return (EINVAL);

	error = falloc(td, &fp, &fd, uap->flags);
	if (error)
		return (error);

	/* Allocate the actual pseudo-TTY. */
	error = pts_alloc(FFLAGS(uap->flags & O_ACCMODE), td, fp);
	if (error != 0) {
		fdclose(td, fp, fd);
		fdrop(fp, td);
		return (error);
	}

	/* Pass it back to userspace. */
	td->td_retval[0] = fd;
	fdrop(fp, td);

	return (0);
}