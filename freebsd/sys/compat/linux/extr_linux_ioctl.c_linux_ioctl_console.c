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
struct vt_mode {int /*<<< orphan*/  frsig; void* acqsig; void* relsig; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct linux_ioctl_args {int cmd; scalar_t__ arg; int /*<<< orphan*/  fd; } ;
struct ioctl_args {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  mode ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTL ; 
 int KDGETLED ; 
 int KDGETMODE ; 
 int KDGKBMODE ; 
 int KDMKTONE ; 
 int KDSETLED ; 
 int KDSETMODE ; 
 int /*<<< orphan*/  KDSKBMODE ; 
 int KIOCSOUND ; 
 int K_RAW ; 
 int K_XLATE ; 
#define  LINUX_KBD_MEDIUMRAW 145 
#define  LINUX_KBD_RAW 144 
#define  LINUX_KBD_XLATE 143 
#define  LINUX_KDGETLED 142 
#define  LINUX_KDGETMODE 141 
#define  LINUX_KDGKBMODE 140 
#define  LINUX_KDMKTONE 139 
#define  LINUX_KDSETLED 138 
#define  LINUX_KDSETMODE 137 
#define  LINUX_KDSKBMODE 136 
#define  LINUX_KIOCSOUND 135 
 int /*<<< orphan*/  LINUX_SIG_VALID (void*) ; 
#define  LINUX_VT_ACTIVATE 134 
#define  LINUX_VT_GETMODE 133 
#define  LINUX_VT_GETSTATE 132 
#define  LINUX_VT_OPENQRY 131 
#define  LINUX_VT_RELDISP 130 
#define  LINUX_VT_SETMODE 129 
#define  LINUX_VT_WAITACTIVE 128 
 int VT_ACTIVATE ; 
 int VT_GETACTIVE ; 
 int VT_GETMODE ; 
 int VT_OPENQRY ; 
 int VT_RELDISP ; 
 int VT_SETMODE ; 
 int VT_WAITACTIVE ; 
 int /*<<< orphan*/  cap_ioctl_rights ; 
 int copyin (void*,struct vt_mode*,int) ; 
 int copyout (struct vt_mode*,void*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int fo_ioctl (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 void* linux_to_bsd_signal (void*) ; 
 int sys_ioctl (struct thread*,struct ioctl_args*) ; 

__attribute__((used)) static int
linux_ioctl_console(struct thread *td, struct linux_ioctl_args *args)
{
	struct file *fp;
	int error;

	error = fget(td, args->fd, &cap_ioctl_rights, &fp);
	if (error != 0)
		return (error);
	switch (args->cmd & 0xffff) {

	case LINUX_KIOCSOUND:
		args->cmd = KIOCSOUND;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_KDMKTONE:
		args->cmd = KDMKTONE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_KDGETLED:
		args->cmd = KDGETLED;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_KDSETLED:
		args->cmd = KDSETLED;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_KDSETMODE:
		args->cmd = KDSETMODE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_KDGETMODE:
		args->cmd = KDGETMODE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_KDGKBMODE:
		args->cmd = KDGKBMODE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_KDSKBMODE: {
		int kbdmode;
		switch (args->arg) {
		case LINUX_KBD_RAW:
			kbdmode = K_RAW;
			break;
		case LINUX_KBD_XLATE:
			kbdmode = K_XLATE;
			break;
		case LINUX_KBD_MEDIUMRAW:
			kbdmode = K_RAW;
			break;
		default:
			fdrop(fp, td);
			return (EINVAL);
		}
		error = (fo_ioctl(fp, KDSKBMODE, (caddr_t)&kbdmode,
		    td->td_ucred, td));
		break;
	}

	case LINUX_VT_OPENQRY:
		args->cmd = VT_OPENQRY;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_VT_GETMODE:
		args->cmd = VT_GETMODE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_VT_SETMODE: {
		struct vt_mode mode;
		if ((error = copyin((void *)args->arg, &mode, sizeof(mode))))
			break;
		if (LINUX_SIG_VALID(mode.relsig))
			mode.relsig = linux_to_bsd_signal(mode.relsig);
		else
			mode.relsig = 0;
		if (LINUX_SIG_VALID(mode.acqsig))
			mode.acqsig = linux_to_bsd_signal(mode.acqsig);
		else
			mode.acqsig = 0;
		/* XXX. Linux ignores frsig and set it to 0. */
		mode.frsig = 0;
		if ((error = copyout(&mode, (void *)args->arg, sizeof(mode))))
			break;
		args->cmd = VT_SETMODE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;
	}

	case LINUX_VT_GETSTATE:
		args->cmd = VT_GETACTIVE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_VT_RELDISP:
		args->cmd = VT_RELDISP;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_VT_ACTIVATE:
		args->cmd = VT_ACTIVATE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	case LINUX_VT_WAITACTIVE:
		args->cmd = VT_WAITACTIVE;
		error = (sys_ioctl(td, (struct ioctl_args *)args));
		break;

	default:
		error = ENOIOCTL;
		break;
	}

	fdrop(fp, td);
	return (error);
}