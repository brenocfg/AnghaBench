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
typedef  int /*<<< orphan*/  umode_t ;
struct fsi_slave {int /*<<< orphan*/  cdev_idx; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct fsi_slave* to_fsi_slave (struct device*) ; 

__attribute__((used)) static char *cfam_devnode(struct device *dev, umode_t *mode,
			  kuid_t *uid, kgid_t *gid)
{
	struct fsi_slave *slave = to_fsi_slave(dev);

#ifdef CONFIG_FSI_NEW_DEV_NODE
	return kasprintf(GFP_KERNEL, "fsi/cfam%d", slave->cdev_idx);
#else
	return kasprintf(GFP_KERNEL, "cfam%d", slave->cdev_idx);
#endif
}