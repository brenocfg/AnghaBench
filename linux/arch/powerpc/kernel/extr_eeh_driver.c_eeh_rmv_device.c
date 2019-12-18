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
struct pci_driver {TYPE_1__* err_handler; } ;
struct pci_dn {int /*<<< orphan*/  pe_number; int /*<<< orphan*/  vf_index; } ;
struct pci_dev {scalar_t__ hdr_type; } ;
struct eeh_rmv_data {int /*<<< orphan*/  removed_vf_list; int /*<<< orphan*/  removed_dev_count; } ;
struct eeh_dev {int /*<<< orphan*/  rmv_entry; int /*<<< orphan*/ * pdev; scalar_t__ physfn; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {scalar_t__ slot_reset; scalar_t__ error_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_DEV_DISCONNECTED ; 
 int /*<<< orphan*/  IODA_INVALID_PE ; 
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 struct pci_dev* eeh_dev_to_pci_dev (struct eeh_dev*) ; 
 struct pci_dn* eeh_dev_to_pdn (struct eeh_dev*) ; 
 int /*<<< orphan*/  eeh_edev_actionable (struct eeh_dev*) ; 
 struct pci_driver* eeh_pcid_get (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_pcid_put (struct pci_dev*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iov_remove_virtfn (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eeh_rmv_device(struct eeh_dev *edev, void *userdata)
{
	struct pci_driver *driver;
	struct pci_dev *dev = eeh_dev_to_pci_dev(edev);
	struct eeh_rmv_data *rmv_data = (struct eeh_rmv_data *)userdata;

	/*
	 * Actually, we should remove the PCI bridges as well.
	 * However, that's lots of complexity to do that,
	 * particularly some of devices under the bridge might
	 * support EEH. So we just care about PCI devices for
	 * simplicity here.
	 */
	if (!eeh_edev_actionable(edev) ||
	    (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE))
		return;

	if (rmv_data) {
		driver = eeh_pcid_get(dev);
		if (driver) {
			if (driver->err_handler &&
			    driver->err_handler->error_detected &&
			    driver->err_handler->slot_reset) {
				eeh_pcid_put(dev);
				return;
			}
			eeh_pcid_put(dev);
		}
	}

	/* Remove it from PCI subsystem */
	pr_info("EEH: Removing %s without EEH sensitive driver\n",
		pci_name(dev));
	edev->mode |= EEH_DEV_DISCONNECTED;
	if (rmv_data)
		rmv_data->removed_dev_count++;

	if (edev->physfn) {
#ifdef CONFIG_PCI_IOV
		struct pci_dn *pdn = eeh_dev_to_pdn(edev);

		pci_iov_remove_virtfn(edev->physfn, pdn->vf_index);
		edev->pdev = NULL;

		/*
		 * We have to set the VF PE number to invalid one, which is
		 * required to plug the VF successfully.
		 */
		pdn->pe_number = IODA_INVALID_PE;
#endif
		if (rmv_data)
			list_add(&edev->rmv_entry, &rmv_data->removed_vf_list);
	} else {
		pci_lock_rescan_remove();
		pci_stop_and_remove_bus_device(dev);
		pci_unlock_rescan_remove();
	}
}