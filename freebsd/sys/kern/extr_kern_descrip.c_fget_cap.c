#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_proc; } ;
struct filedesc {TYPE_2__* fd_ofiles; } ;
struct filecaps {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  seqc_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_4__ {int /*<<< orphan*/  fde_caps; } ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  fd_modified (struct filedesc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget_cap_locked (struct filedesc*,int,int /*<<< orphan*/ *,struct file**,struct filecaps*) ; 
 int fget_unlocked (struct filedesc*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fhold (struct file*) ; 
 int /*<<< orphan*/  filecaps_copy (int /*<<< orphan*/ *,struct filecaps*,int) ; 
 int /*<<< orphan*/  filecaps_fill (struct filecaps*) ; 

int
fget_cap(struct thread *td, int fd, cap_rights_t *needrightsp,
    struct file **fpp, struct filecaps *havecapsp)
{
	struct filedesc *fdp = td->td_proc->p_fd;
	int error;
#ifndef CAPABILITIES
	error = fget_unlocked(fdp, fd, needrightsp, fpp, NULL);
	if (error == 0 && havecapsp != NULL)
		filecaps_fill(havecapsp);
#else
	struct file *fp;
	seqc_t seq;

	for (;;) {
		error = fget_unlocked(fdp, fd, needrightsp, &fp, &seq);
		if (error != 0)
			return (error);

		if (havecapsp != NULL) {
			if (!filecaps_copy(&fdp->fd_ofiles[fd].fde_caps,
			    havecapsp, false)) {
				fdrop(fp, td);
				goto get_locked;
			}
		}

		if (!fd_modified(fdp, fd, seq))
			break;
		fdrop(fp, td);
	}

	*fpp = fp;
	return (0);

get_locked:
	FILEDESC_SLOCK(fdp);
	error = fget_cap_locked(fdp, fd, needrightsp, fpp, havecapsp);
	if (error == 0 && !fhold(*fpp))
		error = EBADF;
	FILEDESC_SUNLOCK(fdp);
#endif
	return (error);
}