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
struct uio {scalar_t__ uio_resid; struct thread* uio_td; } ;
struct ucred {int dummy; } ;
struct thread {struct file* td_fpop; } ;
struct file {int f_flag; } ;
struct cdevsw {int (* d_write ) (struct cdev*,struct uio*,int) ;} ;
struct cdev {int /*<<< orphan*/  si_ctime; int /*<<< orphan*/  si_mtime; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int (* fo_write ) (struct file*,struct uio*,struct ucred*,int,struct thread*) ;} ;

/* Variables and functions */
 scalar_t__ DEVFS_IOSIZE_MAX ; 
 int EINVAL ; 
 int FOF_NEXTOFF ; 
 int FOF_NOLOCK ; 
 int IO_DIRECT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int O_DIRECT ; 
 int O_FSYNC ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int devfs_fp_check (struct file*,struct cdev**,struct cdevsw**,int*) ; 
 int /*<<< orphan*/  devfs_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foffset_lock_uio (struct file*,struct uio*,int) ; 
 int /*<<< orphan*/  foffset_unlock_uio (struct file*,struct uio*,int) ; 
 int stub1 (struct file*,struct uio*,struct ucred*,int,struct thread*) ; 
 int stub2 (struct cdev*,struct uio*,int) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
devfs_write_f(struct file *fp, struct uio *uio, struct ucred *cred,
    int flags, struct thread *td)
{
	struct cdev *dev;
	int error, ioflag, ref;
	ssize_t resid;
	struct cdevsw *dsw;
	struct file *fpop;

	if (uio->uio_resid > DEVFS_IOSIZE_MAX)
		return (EINVAL);
	fpop = td->td_fpop;
	error = devfs_fp_check(fp, &dev, &dsw, &ref);
	if (error != 0) {
		error = vnops.fo_write(fp, uio, cred, flags, td);
		return (error);
	}
	KASSERT(uio->uio_td == td, ("uio_td %p is not td %p", uio->uio_td, td));
	ioflag = fp->f_flag & (O_NONBLOCK | O_DIRECT | O_FSYNC);
	if (ioflag & O_DIRECT)
		ioflag |= IO_DIRECT;
	foffset_lock_uio(fp, uio, flags | FOF_NOLOCK);

	resid = uio->uio_resid;

	error = dsw->d_write(dev, uio, ioflag);
	if (uio->uio_resid != resid || (error == 0 && resid != 0)) {
		devfs_timestamp(&dev->si_ctime);
		dev->si_mtime = dev->si_ctime;
	}
	td->td_fpop = fpop;
	dev_relthread(dev, ref);

	foffset_unlock_uio(fp, uio, flags | FOF_NOLOCK | FOF_NEXTOFF);
	return (error);
}