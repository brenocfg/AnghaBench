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
 int IPMICTL_GET_MY_ADDRESS_CMD ; 
 int IPMICTL_GET_MY_LUN_CMD ; 
#define  L_IPMICTL_GET_MY_ADDRESS_CMD 129 
#define  L_IPMICTL_GET_MY_LUN_CMD 128 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int fo_ioctl (struct file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
ipmi_linux_ioctl(struct thread *td, struct linux_ioctl_args *args)
{
	cap_rights_t rights;
	struct file *fp;
	u_long cmd;
	int error;

	error = fget(td, args->fd, cap_rights_init(&rights, CAP_IOCTL), &fp);
	if (error != 0)
		return (error);
	cmd = args->cmd;

	switch(cmd) {
	case L_IPMICTL_GET_MY_ADDRESS_CMD:
		cmd = IPMICTL_GET_MY_ADDRESS_CMD;
		break;
	case L_IPMICTL_GET_MY_LUN_CMD:
		cmd = IPMICTL_GET_MY_LUN_CMD;
		break;
	}
	/*
	 * Pass the ioctl off to our standard handler.
	 */
	error = (fo_ioctl(fp, cmd, (caddr_t)args->arg, td->td_ucred, td));
	fdrop(fp, td);
	return (error);
}