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
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
#define  CDEV_IOCTL1 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev2udev (struct cdev*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
mydev_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int mode,
    struct thread *td)
{
    int error = 0;
    struct proc *procp = td->td_proc;

    printf("mydev_ioctl: dev_t=%lu, cmd=%lx, arg=%p, mode=%x procp=%p\n",
	   dev2udev(dev), cmd, arg, mode, procp);

    switch(cmd) {
    case CDEV_IOCTL1:
	printf("you called mydev_ioctl CDEV_IOCTL1\n");
	break;
    default:
	printf("No such ioctl for me!\n");
	error = EINVAL;
	break;
    }
    return (error);
}