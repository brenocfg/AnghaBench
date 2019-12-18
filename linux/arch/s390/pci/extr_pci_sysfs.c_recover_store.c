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
struct zpci_dev {int /*<<< orphan*/  bus; } ;
struct pci_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file_self (struct device*,struct device_attribute*) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_rescan_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (struct pci_dev*) ; 
 int zpci_disable_device (struct zpci_dev*) ; 
 int zpci_enable_device (struct zpci_dev*) ; 

__attribute__((used)) static ssize_t recover_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct zpci_dev *zdev = to_zpci(pdev);
	int ret;

	if (!device_remove_file_self(dev, attr))
		return count;

	pci_lock_rescan_remove();
	pci_stop_and_remove_bus_device(pdev);
	ret = zpci_disable_device(zdev);
	if (ret)
		goto error;

	ret = zpci_enable_device(zdev);
	if (ret)
		goto error;

	pci_rescan_bus(zdev->bus);
	pci_unlock_rescan_remove();

	return count;

error:
	pci_unlock_rescan_remove();
	return ret;
}