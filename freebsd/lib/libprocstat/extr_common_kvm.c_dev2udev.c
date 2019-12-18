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
struct cdev_priv {scalar_t__ cdp_inode; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  priv ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ cdev2priv (struct cdev*) ; 
 scalar_t__ kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct cdev_priv*,int) ; 
 int /*<<< orphan*/  warnx (char*,struct cdev*) ; 

dev_t
dev2udev(kvm_t *kd, struct cdev *dev)
{
	struct cdev_priv priv;

	assert(kd);
	if (kvm_read_all(kd, (unsigned long)cdev2priv(dev), &priv,
	    sizeof(priv))) {
		return ((dev_t)priv.cdp_inode);
	} else {
		warnx("can't convert cdev *%p to a dev_t\n", dev);
		return (-1);
	}
}