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
struct linux_ioctl_args {int cmd; } ;
struct ioctl_args {int dummy; } ;

/* Variables and functions */
 int ENOIOCTL ; 
#define  LINUX_SIOCGIFADDR 130 
#define  LINUX_SIOCGIFFLAGS 129 
#define  LINUX_SIOCSIFADDR 128 
 int SIOCGIFADDR ; 
 int SIOCGIFFLAGS ; 
 int SIOCSIFADDR ; 
 int sys_ioctl (struct thread*,struct ioctl_args*) ; 

__attribute__((used)) static int
linux_ioctl_special(struct thread *td, struct linux_ioctl_args *args)
{
	int error;

	switch (args->cmd) {
	case LINUX_SIOCGIFADDR:
		args->cmd = SIOCGIFADDR;
		error = sys_ioctl(td, (struct ioctl_args *)args);
		break;
	case LINUX_SIOCSIFADDR:
		args->cmd = SIOCSIFADDR;
		error = sys_ioctl(td, (struct ioctl_args *)args);
		break;
	case LINUX_SIOCGIFFLAGS:
		args->cmd = SIOCGIFFLAGS;
		error = sys_ioctl(td, (struct ioctl_args *)args);
		break;
	default:
		error = ENOIOCTL;
	}

	return (error);
}