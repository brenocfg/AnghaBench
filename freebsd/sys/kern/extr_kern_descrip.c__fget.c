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
struct file {int f_flag; int /*<<< orphan*/ * f_ops; } ;
typedef  int /*<<< orphan*/  seqc_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EBADF ; 
#define  FEXEC 130 
#define  FREAD 129 
#define  FWRITE 128 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  badfileops ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget_unlocked (struct filedesc*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
_fget(struct thread *td, int fd, struct file **fpp, int flags,
    cap_rights_t *needrightsp, seqc_t *seqp)
{
	struct filedesc *fdp;
	struct file *fp;
	int error;

	*fpp = NULL;
	fdp = td->td_proc->p_fd;
	error = fget_unlocked(fdp, fd, needrightsp, &fp, seqp);
	if (error != 0)
		return (error);
	if (fp->f_ops == &badfileops) {
		fdrop(fp, td);
		return (EBADF);
	}

	/*
	 * FREAD and FWRITE failure return EBADF as per POSIX.
	 */
	error = 0;
	switch (flags) {
	case FREAD:
	case FWRITE:
		if ((fp->f_flag & flags) == 0)
			error = EBADF;
		break;
	case FEXEC:
	    	if ((fp->f_flag & (FREAD | FEXEC)) == 0 ||
		    ((fp->f_flag & FWRITE) != 0))
			error = EBADF;
		break;
	case 0:
		break;
	default:
		KASSERT(0, ("wrong flags"));
	}

	if (error != 0) {
		fdrop(fp, td);
		return (error);
	}

	*fpp = fp;
	return (0);
}