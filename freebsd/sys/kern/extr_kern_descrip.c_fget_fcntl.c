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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  seqc_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FCNTL ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int cap_fcntl_check (struct filedesc*,int,int) ; 
 int /*<<< orphan*/  cap_rights_is_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_modified (struct filedesc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget_unlocked (struct filedesc*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *) ; 

int
fget_fcntl(struct thread *td, int fd, cap_rights_t *rightsp, int needfcntl,
    struct file **fpp)
{
	struct filedesc *fdp = td->td_proc->p_fd;
#ifndef CAPABILITIES
	return (fget_unlocked(fdp, fd, rightsp, fpp, NULL));
#else
	int error;
	seqc_t seq;

	MPASS(cap_rights_is_set(rightsp, CAP_FCNTL));
	for (;;) {
		error = fget_unlocked(fdp, fd, rightsp, fpp, &seq);
		if (error != 0)
			return (error);
		error = cap_fcntl_check(fdp, fd, needfcntl);
		if (!fd_modified(fdp, fd, seq))
			break;
		fdrop(*fpp, td);
	}
	if (error != 0) {
		fdrop(*fpp, td);
		*fpp = NULL;
	}
	return (error);
#endif
}