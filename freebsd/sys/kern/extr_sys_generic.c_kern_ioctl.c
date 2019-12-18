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
typedef  int u_long ;
struct thread {int /*<<< orphan*/  td_ucred; TYPE_1__* td_proc; } ;
struct filedesc {TYPE_2__* fd_ofiles; } ;
struct file {int f_flag; } ;
typedef  void* caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  fde_flags; } ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_CMD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int EBADF ; 
 int /*<<< orphan*/  FASYNC ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_UNLOCK_ASSERT (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
#define  FIOASYNC 133 
#define  FIOCLEX 132 
#define  FIONBIO 131 
#define  FIONCLEX 130 
 int /*<<< orphan*/  FNONBLOCK ; 
 int FREAD ; 
 int FWRITE ; 
#define  LA_SLOCKED 129 
 int LA_UNLOCKED ; 
#define  LA_XLOCKED 128 
 int /*<<< orphan*/  UF_EXCLOSE ; 
 int /*<<< orphan*/  atomic_clear_int (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int /*<<< orphan*/ ) ; 
 int cap_ioctl_check (struct filedesc*,int,int) ; 
 int /*<<< orphan*/  cap_ioctl_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 struct file* fget_locked (struct filedesc*,int) ; 
 int /*<<< orphan*/  fhold (struct file*) ; 
 int fo_ioctl (struct file*,int,void*,int /*<<< orphan*/ ,struct thread*) ; 

int
kern_ioctl(struct thread *td, int fd, u_long com, caddr_t data)
{
	struct file *fp;
	struct filedesc *fdp;
	int error, tmp, locked;

	AUDIT_ARG_FD(fd);
	AUDIT_ARG_CMD(com);

	fdp = td->td_proc->p_fd;

	switch (com) {
	case FIONCLEX:
	case FIOCLEX:
		FILEDESC_XLOCK(fdp);
		locked = LA_XLOCKED;
		break;
	default:
#ifdef CAPABILITIES
		FILEDESC_SLOCK(fdp);
		locked = LA_SLOCKED;
#else
		locked = LA_UNLOCKED;
#endif
		break;
	}

#ifdef CAPABILITIES
	if ((fp = fget_locked(fdp, fd)) == NULL) {
		error = EBADF;
		goto out;
	}
	if ((error = cap_ioctl_check(fdp, fd, com)) != 0) {
		fp = NULL;	/* fhold() was not called yet */
		goto out;
	}
	if (!fhold(fp)) {
		error = EBADF;
		fp = NULL;
		goto out;
	}
	if (locked == LA_SLOCKED) {
		FILEDESC_SUNLOCK(fdp);
		locked = LA_UNLOCKED;
	}
#else
	error = fget(td, fd, &cap_ioctl_rights, &fp);
	if (error != 0) {
		fp = NULL;
		goto out;
	}
#endif
	if ((fp->f_flag & (FREAD | FWRITE)) == 0) {
		error = EBADF;
		goto out;
	}

	switch (com) {
	case FIONCLEX:
		fdp->fd_ofiles[fd].fde_flags &= ~UF_EXCLOSE;
		goto out;
	case FIOCLEX:
		fdp->fd_ofiles[fd].fde_flags |= UF_EXCLOSE;
		goto out;
	case FIONBIO:
		if ((tmp = *(int *)data))
			atomic_set_int(&fp->f_flag, FNONBLOCK);
		else
			atomic_clear_int(&fp->f_flag, FNONBLOCK);
		data = (void *)&tmp;
		break;
	case FIOASYNC:
		if ((tmp = *(int *)data))
			atomic_set_int(&fp->f_flag, FASYNC);
		else
			atomic_clear_int(&fp->f_flag, FASYNC);
		data = (void *)&tmp;
		break;
	}

	error = fo_ioctl(fp, com, data, td->td_ucred, td);
out:
	switch (locked) {
	case LA_XLOCKED:
		FILEDESC_XUNLOCK(fdp);
		break;
#ifdef CAPABILITIES
	case LA_SLOCKED:
		FILEDESC_SUNLOCK(fdp);
		break;
#endif
	default:
		FILEDESC_UNLOCK_ASSERT(fdp);
		break;
	}
	if (fp != NULL)
		fdrop(fp, td);
	return (error);
}