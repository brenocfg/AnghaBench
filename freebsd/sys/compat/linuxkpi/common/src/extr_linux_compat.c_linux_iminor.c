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
struct linux_cdev {int /*<<< orphan*/  dev; } ;
struct inode {TYPE_1__* v_rdev; } ;
struct TYPE_2__ {struct linux_cdev* si_drv1; int /*<<< orphan*/ * si_devsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  linuxcdevsw ; 
 unsigned int minor (int /*<<< orphan*/ ) ; 

unsigned int
linux_iminor(struct inode *inode)
{
	struct linux_cdev *ldev;

	if (inode == NULL || inode->v_rdev == NULL ||
	    inode->v_rdev->si_devsw != &linuxcdevsw)
		return (-1U);
	ldev = inode->v_rdev->si_drv1;
	if (ldev == NULL)
		return (-1U);

	return (minor(ldev->dev));
}