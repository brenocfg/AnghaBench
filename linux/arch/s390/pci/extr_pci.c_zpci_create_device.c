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
struct zpci_dev {scalar_t__ state; int /*<<< orphan*/  entry; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ ZPCI_FN_STATE_CONFIGURED ; 
 scalar_t__ ZPCI_FN_STATE_ONLINE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int zpci_alloc_domain (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_destroy_iommu (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_disable_device (struct zpci_dev*) ; 
 int zpci_enable_device (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_free_domain (struct zpci_dev*) ; 
 int zpci_init_iommu (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_init_slot (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_list ; 
 int /*<<< orphan*/  zpci_list_lock ; 
 int zpci_scan_bus (struct zpci_dev*) ; 

int zpci_create_device(struct zpci_dev *zdev)
{
	int rc;

	rc = zpci_alloc_domain(zdev);
	if (rc)
		goto out;

	rc = zpci_init_iommu(zdev);
	if (rc)
		goto out_free;

	mutex_init(&zdev->lock);
	if (zdev->state == ZPCI_FN_STATE_CONFIGURED) {
		rc = zpci_enable_device(zdev);
		if (rc)
			goto out_destroy_iommu;
	}
	rc = zpci_scan_bus(zdev);
	if (rc)
		goto out_disable;

	spin_lock(&zpci_list_lock);
	list_add_tail(&zdev->entry, &zpci_list);
	spin_unlock(&zpci_list_lock);

	zpci_init_slot(zdev);

	return 0;

out_disable:
	if (zdev->state == ZPCI_FN_STATE_ONLINE)
		zpci_disable_device(zdev);
out_destroy_iommu:
	zpci_destroy_iommu(zdev);
out_free:
	zpci_free_domain(zdev);
out:
	return rc;
}