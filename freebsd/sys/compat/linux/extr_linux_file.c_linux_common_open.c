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
struct thread {int* td_retval; int /*<<< orphan*/  td_ucred; struct proc* td_proc; } ;
struct proc {int p_flag; } ;
struct file {scalar_t__ f_type; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_FASYNC ; 
 int LINUX_O_ACCMODE ; 
 int LINUX_O_APPEND ; 
 int LINUX_O_CLOEXEC ; 
 int LINUX_O_CREAT ; 
 int LINUX_O_DIRECT ; 
 int LINUX_O_DIRECTORY ; 
 int LINUX_O_EXCL ; 
 int LINUX_O_NDELAY ; 
 int LINUX_O_NOCTTY ; 
 int LINUX_O_NOFOLLOW ; 
 int LINUX_O_NONBLOCK ; 
#define  LINUX_O_RDWR 129 
 int LINUX_O_SYNC ; 
 int LINUX_O_TRUNC ; 
#define  LINUX_O_WRONLY 128 
 int O_APPEND ; 
 int O_ASYNC ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_DIRECT ; 
 int O_DIRECTORY ; 
 int O_EXCL ; 
 int O_FSYNC ; 
 int O_NOCTTY ; 
 int O_NOFOLLOW ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_CONTROLT ; 
 scalar_t__ SESS_LEADER (struct proc*) ; 
 int /*<<< orphan*/  TIOCSCTTY ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  cap_ioctl_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 scalar_t__ fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  fo_ioctl (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int kern_openat (struct thread*,int,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_common_open(struct thread *td, int dirfd, char *path, int l_flags, int mode)
{
	struct proc *p = td->td_proc;
	struct file *fp;
	int fd;
	int bsd_flags, error;

	bsd_flags = 0;
	switch (l_flags & LINUX_O_ACCMODE) {
	case LINUX_O_WRONLY:
		bsd_flags |= O_WRONLY;
		break;
	case LINUX_O_RDWR:
		bsd_flags |= O_RDWR;
		break;
	default:
		bsd_flags |= O_RDONLY;
	}
	if (l_flags & LINUX_O_NDELAY)
		bsd_flags |= O_NONBLOCK;
	if (l_flags & LINUX_O_APPEND)
		bsd_flags |= O_APPEND;
	if (l_flags & LINUX_O_SYNC)
		bsd_flags |= O_FSYNC;
	if (l_flags & LINUX_O_CLOEXEC)
		bsd_flags |= O_CLOEXEC;
	if (l_flags & LINUX_O_NONBLOCK)
		bsd_flags |= O_NONBLOCK;
	if (l_flags & LINUX_FASYNC)
		bsd_flags |= O_ASYNC;
	if (l_flags & LINUX_O_CREAT)
		bsd_flags |= O_CREAT;
	if (l_flags & LINUX_O_TRUNC)
		bsd_flags |= O_TRUNC;
	if (l_flags & LINUX_O_EXCL)
		bsd_flags |= O_EXCL;
	if (l_flags & LINUX_O_NOCTTY)
		bsd_flags |= O_NOCTTY;
	if (l_flags & LINUX_O_DIRECT)
		bsd_flags |= O_DIRECT;
	if (l_flags & LINUX_O_NOFOLLOW)
		bsd_flags |= O_NOFOLLOW;
	if (l_flags & LINUX_O_DIRECTORY)
		bsd_flags |= O_DIRECTORY;
	/* XXX LINUX_O_NOATIME: unable to be easily implemented. */

	error = kern_openat(td, dirfd, path, UIO_SYSSPACE, bsd_flags, mode);
	if (error != 0)
		goto done;
	if (bsd_flags & O_NOCTTY)
		goto done;

	/*
	 * XXX In between kern_openat() and fget(), another process
	 * having the same filedesc could use that fd without
	 * checking below.
	*/
	fd = td->td_retval[0];
	if (fget(td, fd, &cap_ioctl_rights, &fp) == 0) {
		if (fp->f_type != DTYPE_VNODE) {
			fdrop(fp, td);
			goto done;
		}
		sx_slock(&proctree_lock);
		PROC_LOCK(p);
		if (SESS_LEADER(p) && !(p->p_flag & P_CONTROLT)) {
			PROC_UNLOCK(p);
			sx_sunlock(&proctree_lock);
			/* XXXPJD: Verify if TIOCSCTTY is allowed. */
			(void) fo_ioctl(fp, TIOCSCTTY, (caddr_t) 0,
			    td->td_ucred, td);
		} else {
			PROC_UNLOCK(p);
			sx_sunlock(&proctree_lock);
		}
		fdrop(fp, td);
	}

done:
	LFREEPATH(path);
	return (error);
}