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
struct thread {int dummy; } ;
struct ioctl_args {int com; int /*<<< orphan*/  fd; } ;
struct freebsd32_ioctl_args {int com; int /*<<< orphan*/  fd; } ;
struct file {int f_flag; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
 int EBADF ; 
 int FREAD ; 
 int FWRITE ; 
#define  MEMRANGE_GET32 131 
#define  MEMRANGE_SET32 130 
#define  PCIOCBARMMAP_32 129 
 int /*<<< orphan*/  PTRIN_CP (struct freebsd32_ioctl_args,struct ioctl_args,int /*<<< orphan*/ ) ; 
#define  SG_IO_32 128 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int freebsd32_ioctl_barmmap (struct thread*,struct freebsd32_ioctl_args*,struct file*) ; 
 int freebsd32_ioctl_memrange (struct thread*,struct freebsd32_ioctl_args*,struct file*) ; 
 int freebsd32_ioctl_sg (struct thread*,struct freebsd32_ioctl_args*,struct file*) ; 
 int sys_ioctl (struct thread*,struct ioctl_args*) ; 

int
freebsd32_ioctl(struct thread *td, struct freebsd32_ioctl_args *uap)
{
	struct ioctl_args ap /*{
		int	fd;
		u_long	com;
		caddr_t	data;
	}*/ ;
	struct file *fp;
	cap_rights_t rights;
	int error;

	error = fget(td, uap->fd, cap_rights_init(&rights, CAP_IOCTL), &fp);
	if (error != 0)
		return (error);
	if ((fp->f_flag & (FREAD | FWRITE)) == 0) {
		fdrop(fp, td);
		return (EBADF);
	}

	switch (uap->com) {
	case MEMRANGE_GET32:	/* FALLTHROUGH */
	case MEMRANGE_SET32:
		error = freebsd32_ioctl_memrange(td, uap, fp);
		break;

	case SG_IO_32:
		error = freebsd32_ioctl_sg(td, uap, fp);
		break;

	case PCIOCBARMMAP_32:
		error = freebsd32_ioctl_barmmap(td, uap, fp);
		break;

	default:
		fdrop(fp, td);
		ap.fd = uap->fd;
		ap.com = uap->com;
		PTRIN_CP(*uap, ap, data);
		return sys_ioctl(td, &ap);
	}

	fdrop(fp, td);
	return (error);
}