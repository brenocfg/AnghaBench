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
struct cdev {int dummy; } ;

/* Variables and functions */
 int FEXCL ; 
 int /*<<< orphan*/  cr ; 
 scalar_t__ getminor (struct cdev) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otyp ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int zfs_ctldev_init (struct cdev*) ; 
 int zvol_open (struct cdev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfsdev_open(struct cdev *devp, int flag, int mode, struct thread *td)
{
	int error = 0;

#ifdef illumos
	if (getminor(*devp) != 0)
		return (zvol_open(devp, flag, otyp, cr));
#endif

	/* This is the control device. Allocate a new minor if requested. */
	if (flag & FEXCL) {
		mutex_enter(&spa_namespace_lock);
		error = zfs_ctldev_init(devp);
		mutex_exit(&spa_namespace_lock);
	}

	return (error);
}