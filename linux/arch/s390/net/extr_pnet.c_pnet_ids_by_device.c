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
typedef  int /*<<< orphan*/  u8 ;
struct zpci_dev {int /*<<< orphan*/ * util_str; } ;
struct device {int dummy; } ;
struct ccwgroup_device {int /*<<< orphan*/ * cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (int /*<<< orphan*/ *,int) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int PNETIDS_LEN ; 
 int /*<<< orphan*/ * ccw_device_get_util_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_ccwgroup (struct device*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnet_ids_by_device(struct device *dev, u8 *pnetids)
{
	memset(pnetids, 0, PNETIDS_LEN);
	if (dev_is_ccwgroup(dev)) {
		struct ccwgroup_device *gdev = to_ccwgroupdev(dev);
		u8 *util_str;

		util_str = ccw_device_get_util_str(gdev->cdev[0], 0);
		if (!util_str)
			return -ENOMEM;
		memcpy(pnetids, util_str, PNETIDS_LEN);
		EBCASC(pnetids, PNETIDS_LEN);
		kfree(util_str);
		return 0;
	}
	if (dev_is_pci(dev)) {
		struct zpci_dev *zdev = to_zpci(to_pci_dev(dev));

		memcpy(pnetids, zdev->util_str, sizeof(zdev->util_str));
		EBCASC(pnetids, sizeof(zdev->util_str));
		return 0;
	}
	return -EOPNOTSUPP;
}