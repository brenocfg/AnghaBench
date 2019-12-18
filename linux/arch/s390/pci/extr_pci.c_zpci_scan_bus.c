#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zpci_dev {TYPE_1__* bus; int /*<<< orphan*/  max_bus_speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_bus_speed; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPCI_BUS_NR ; 
 int /*<<< orphan*/  pci_bus_add_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_free_resource_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_root_ops ; 
 TYPE_1__* pci_scan_root_bus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct zpci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resources ; 
 int /*<<< orphan*/  zpci_cleanup_bus_resources (struct zpci_dev*) ; 
 int zpci_setup_bus_resources (struct zpci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zpci_scan_bus(struct zpci_dev *zdev)
{
	LIST_HEAD(resources);
	int ret;

	ret = zpci_setup_bus_resources(zdev, &resources);
	if (ret)
		goto error;

	zdev->bus = pci_scan_root_bus(NULL, ZPCI_BUS_NR, &pci_root_ops,
				      zdev, &resources);
	if (!zdev->bus) {
		ret = -EIO;
		goto error;
	}
	zdev->bus->max_bus_speed = zdev->max_bus_speed;
	pci_bus_add_devices(zdev->bus);
	return 0;

error:
	zpci_cleanup_bus_resources(zdev);
	pci_free_resource_list(&resources);
	return ret;
}