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
typedef  int /*<<< orphan*/  u_char ;
struct thread {TYPE_1__* td_proc; } ;
struct filedesc {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  seqc_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MMAP ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int _fget (struct thread*,int,struct file**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_rights (struct filedesc*,int) ; 
 int /*<<< orphan*/  cap_rights_is_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_rights_to_vmprot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fd_modified (struct filedesc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 

int
fget_mmap(struct thread *td, int fd, cap_rights_t *rightsp, u_char *maxprotp,
    struct file **fpp)
{
	int error;
#ifndef CAPABILITIES
	error = _fget(td, fd, fpp, 0, rightsp, NULL);
	if (maxprotp != NULL)
		*maxprotp = VM_PROT_ALL;
#else
	cap_rights_t fdrights;
	struct filedesc *fdp = td->td_proc->p_fd;
	seqc_t seq;

	MPASS(cap_rights_is_set(rightsp, CAP_MMAP));
	for (;;) {
		error = _fget(td, fd, fpp, 0, rightsp, &seq);
		if (error != 0)
			return (error);
		if (maxprotp != NULL)
			fdrights = *cap_rights(fdp, fd);
		if (!fd_modified(fdp, fd, seq))
			break;
		fdrop(*fpp, td);
	}

	/*
	 * If requested, convert capability rights to access flags.
	 */
	if (maxprotp != NULL)
		*maxprotp = cap_rights_to_vmprot(&fdrights);
#endif
	return (error);
}