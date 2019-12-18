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
typedef  int u_long ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct linux_file {int f_flags; int /*<<< orphan*/  f_sigio; } ;
struct linux_cdev {int dummy; } ;
struct file_operations {int /*<<< orphan*/  (* fasync ) (int /*<<< orphan*/ ,struct linux_file*,int) ;} ;
struct file {int f_flag; scalar_t__ f_data; } ;

/* Variables and functions */
 int FASYNC ; 
#define  FIOASYNC 131 
#define  FIOGETOWN 130 
#define  FIONBIO 129 
#define  FIOSETOWN 128 
 int OPW (struct file*,struct thread*,int /*<<< orphan*/ ) ; 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_drop_fop (struct linux_cdev*) ; 
 int linux_file_ioctl_sub (struct file*,struct linux_file*,struct file_operations const*,int,void*,struct thread*) ; 
 int /*<<< orphan*/  linux_get_fop (struct linux_file*,struct file_operations const**,struct linux_cdev**) ; 
 int /*<<< orphan*/  linux_set_current (struct thread*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct linux_file*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct linux_file*,int) ; 

__attribute__((used)) static int
linux_file_ioctl(struct file *fp, u_long cmd, void *data, struct ucred *cred,
    struct thread *td)
{
	struct linux_file *filp;
	const struct file_operations *fop;
	struct linux_cdev *ldev;
	int error;

	error = 0;
	filp = (struct linux_file *)fp->f_data;
	filp->f_flags = fp->f_flag;
	linux_get_fop(filp, &fop, &ldev);

	linux_set_current(td);
	switch (cmd) {
	case FIONBIO:
		break;
	case FIOASYNC:
		if (fop->fasync == NULL)
			break;
		error = -OPW(fp, td, fop->fasync(0, filp, fp->f_flag & FASYNC));
		break;
	case FIOSETOWN:
		error = fsetown(*(int *)data, &filp->f_sigio);
		if (error == 0) {
			if (fop->fasync == NULL)
				break;
			error = -OPW(fp, td, fop->fasync(0, filp,
			    fp->f_flag & FASYNC));
		}
		break;
	case FIOGETOWN:
		*(int *)data = fgetown(&filp->f_sigio);
		break;
	default:
		error = linux_file_ioctl_sub(fp, filp, fop, cmd, data, td);
		break;
	}
	linux_drop_fop(ldev);
	return (error);
}