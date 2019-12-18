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
typedef  int /*<<< orphan*/  uint8_t ;
struct uio {int uio_iovcnt; scalar_t__ uio_resid; TYPE_1__* uio_iov; int /*<<< orphan*/  uio_offset; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct linux_file {int /*<<< orphan*/  f_flags; } ;
struct linux_cdev {int dummy; } ;
struct file_operations {int /*<<< orphan*/  (* write ) (struct linux_file*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct file {int /*<<< orphan*/  f_flag; scalar_t__ f_data; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 scalar_t__ DEVFS_IOSIZE_MAX ; 
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LINUX_KQ_FLAG_HAS_WRITE ; 
 int OPW (struct file*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  linux_drop_fop (struct linux_cdev*) ; 
 int /*<<< orphan*/  linux_file_kqfilter_poll (struct linux_file*,int /*<<< orphan*/ ) ; 
 int linux_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  linux_get_fop (struct linux_file*,struct file_operations const**,struct linux_cdev**) ; 
 int /*<<< orphan*/  linux_set_current (struct thread*) ; 
 int /*<<< orphan*/  stub1 (struct linux_file*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_file_write(struct file *file, struct uio *uio, struct ucred *active_cred,
    int flags, struct thread *td)
{
	struct linux_file *filp;
	const struct file_operations *fop;
	struct linux_cdev *ldev;
	ssize_t bytes;
	int error;

	filp = (struct linux_file *)file->f_data;
	filp->f_flags = file->f_flag;
	/* XXX no support for I/O vectors currently */
	if (uio->uio_iovcnt != 1)
		return (EOPNOTSUPP);
	if (uio->uio_resid > DEVFS_IOSIZE_MAX)
		return (EINVAL);
	linux_set_current(td);
	linux_get_fop(filp, &fop, &ldev);
	if (fop->write != NULL) {
		bytes = OPW(file, td, fop->write(filp,
		    uio->uio_iov->iov_base,
		    uio->uio_iov->iov_len, &uio->uio_offset));
		if (bytes >= 0) {
			uio->uio_iov->iov_base =
			    ((uint8_t *)uio->uio_iov->iov_base) + bytes;
			uio->uio_iov->iov_len -= bytes;
			uio->uio_resid -= bytes;
			error = 0;
		} else {
			error = linux_get_error(current, -bytes);
		}
	} else
		error = ENXIO;

	/* update kqfilter status, if any */
	linux_file_kqfilter_poll(filp, LINUX_KQ_FLAG_HAS_WRITE);

	linux_drop_fop(ldev);

	return (error);
}