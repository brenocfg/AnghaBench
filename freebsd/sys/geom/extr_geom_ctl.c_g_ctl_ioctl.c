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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENOIOCTL ; 
#define  GEOM_CTL 128 
 int g_ctl_ioctl_ctl (struct cdev*,int,int /*<<< orphan*/ ,int,struct thread*) ; 

__attribute__((used)) static int
g_ctl_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag, struct thread *td)
{
	int error;

	switch(cmd) {
	case GEOM_CTL:
		error = g_ctl_ioctl_ctl(dev, cmd, data, fflag, td);
		break;
	default:
		error = ENOIOCTL;
		break;
	}
	return (error);

}