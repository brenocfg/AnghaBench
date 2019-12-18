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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct linux_ioctl_args {int cmd; scalar_t__ arg; int /*<<< orphan*/  fd; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
#define  MFI_LINUX_CMD 129 
 int MFI_LINUX_CMD_2 ; 
#define  MFI_LINUX_SET_AEN 128 
 int MFI_LINUX_SET_AEN_2 ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int fo_ioctl (struct file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
mfi_linux_ioctl(struct thread *p, struct linux_ioctl_args *args)
{
	cap_rights_t rights;
	struct file *fp;
	int error;
	u_long cmd = args->cmd;

	switch (cmd) {
	case MFI_LINUX_CMD:
		cmd = MFI_LINUX_CMD_2;
		break;
	case MFI_LINUX_SET_AEN:
		cmd = MFI_LINUX_SET_AEN_2;
		break;
	}

	error = fget(p, args->fd, cap_rights_init(&rights, CAP_IOCTL), &fp);
	if (error != 0)
		return (error);
	error = fo_ioctl(fp, cmd, (caddr_t)args->arg, p->td_ucred, p);
	fdrop(fp, p);
	return (error);
}