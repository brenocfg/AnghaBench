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
struct zpci_dev {int /*<<< orphan*/  fid; int /*<<< orphan*/  entry; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 struct zpci_dev* get_zdev_by_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  kfree (struct zpci_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpci_cleanup_bus_resources (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_destroy_iommu (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_exit_slot (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_free_domain (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_list_lock ; 

void pcibios_remove_bus(struct pci_bus *bus)
{
	struct zpci_dev *zdev = get_zdev_by_bus(bus);

	zpci_exit_slot(zdev);
	zpci_cleanup_bus_resources(zdev);
	zpci_destroy_iommu(zdev);
	zpci_free_domain(zdev);

	spin_lock(&zpci_list_lock);
	list_del(&zdev->entry);
	spin_unlock(&zpci_list_lock);

	zpci_dbg(3, "rem fid:%x\n", zdev->fid);
	kfree(zdev);
}