#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_proc; } ;
struct filedesc {int dummy; } ;
struct filecaps {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _finstall (struct filedesc*,struct file*,int,int,struct filecaps*) ; 
 int fdalloc (struct thread*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  fhold (struct file*) ; 

int
finstall(struct thread *td, struct file *fp, int *fd, int flags,
    struct filecaps *fcaps)
{
	struct filedesc *fdp = td->td_proc->p_fd;
	int error;

	MPASS(fd != NULL);

	if (!fhold(fp))
		return (EBADF);
	FILEDESC_XLOCK(fdp);
	if ((error = fdalloc(td, 0, fd))) {
		FILEDESC_XUNLOCK(fdp);
		fdrop(fp, td);
		return (error);
	}
	_finstall(fdp, fp, *fd, flags, fcaps);
	FILEDESC_XUNLOCK(fdp);
	return (0);
}