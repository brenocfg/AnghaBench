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
struct pci_driver {int /*<<< orphan*/  name; int /*<<< orphan*/  err_handler; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct eeh_dev {int mode; struct pci_dev* pdev; int /*<<< orphan*/  pe; } ;
typedef  enum pci_ers_result { ____Placeholder_pci_ers_result } pci_ers_result ;
typedef  int (* eeh_report_fn ) (struct eeh_dev*,struct pci_dev*,struct pci_driver*) ;

/* Variables and functions */
 int EEH_DEV_NO_HANDLER ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeh_dev_removed (struct eeh_dev*) ; 
 scalar_t__ eeh_edev_actionable (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_edev_info (struct eeh_dev*,char*,...) ; 
 int /*<<< orphan*/  eeh_edev_warn (struct eeh_dev*,char*) ; 
 struct pci_driver* eeh_pcid_get (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_pcid_put (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_pe_passed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int pci_ers_merge_result (int,int) ; 
 int /*<<< orphan*/  pci_ers_result_name (int) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eeh_pe_report_edev(struct eeh_dev *edev, eeh_report_fn fn,
			       enum pci_ers_result *result)
{
	struct pci_dev *pdev;
	struct pci_driver *driver;
	enum pci_ers_result new_result;

	pci_lock_rescan_remove();
	pdev = edev->pdev;
	if (pdev)
		get_device(&pdev->dev);
	pci_unlock_rescan_remove();
	if (!pdev) {
		eeh_edev_info(edev, "no device");
		return;
	}
	device_lock(&pdev->dev);
	if (eeh_edev_actionable(edev)) {
		driver = eeh_pcid_get(pdev);

		if (!driver)
			eeh_edev_info(edev, "no driver");
		else if (!driver->err_handler)
			eeh_edev_info(edev, "driver not EEH aware");
		else if (edev->mode & EEH_DEV_NO_HANDLER)
			eeh_edev_info(edev, "driver bound too late");
		else {
			new_result = fn(edev, pdev, driver);
			eeh_edev_info(edev, "%s driver reports: '%s'",
				      driver->name,
				      pci_ers_result_name(new_result));
			if (result)
				*result = pci_ers_merge_result(*result,
							       new_result);
		}
		if (driver)
			eeh_pcid_put(pdev);
	} else {
		eeh_edev_info(edev, "not actionable (%d,%d,%d)", !!pdev,
			      !eeh_dev_removed(edev), !eeh_pe_passed(edev->pe));
	}
	device_unlock(&pdev->dev);
	if (edev->pdev != pdev)
		eeh_edev_warn(edev, "Device changed during processing!\n");
	put_device(&pdev->dev);
}