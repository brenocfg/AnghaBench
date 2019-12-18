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
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  devfn; } ;
struct mem_ctl_info {struct i5400_pvt* pvt_info; } ;
struct i5400_pvt {scalar_t__ maxch; struct pci_dev* branchmap_werrors; struct pci_dev* fsb_error_regs; struct pci_dev* branch_0; int /*<<< orphan*/ * branch_1; struct pci_dev* system_address; } ;

/* Variables and functions */
 scalar_t__ CHANNELS_PER_BRANCH ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_5400_ERR ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_5400_FBD0 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_5400_FBD1 ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i5400_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 void* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 

__attribute__((used)) static int i5400_get_devices(struct mem_ctl_info *mci, int dev_idx)
{
	struct i5400_pvt *pvt;
	struct pci_dev *pdev;

	pvt = mci->pvt_info;
	pvt->branchmap_werrors = NULL;
	pvt->fsb_error_regs = NULL;
	pvt->branch_0 = NULL;
	pvt->branch_1 = NULL;

	/* Attempt to 'get' the MCH register we want */
	pdev = NULL;
	while (1) {
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_5400_ERR, pdev);
		if (!pdev) {
			/* End of list, leave */
			i5400_printk(KERN_ERR,
				"'system address,Process Bus' "
				"device not found:"
				"vendor 0x%x device 0x%x ERR func 1 "
				"(broken BIOS?)\n",
				PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_5400_ERR);
			return -ENODEV;
		}

		/* Store device 16 func 1 */
		if (PCI_FUNC(pdev->devfn) == 1)
			break;
	}
	pvt->branchmap_werrors = pdev;

	pdev = NULL;
	while (1) {
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_5400_ERR, pdev);
		if (!pdev) {
			/* End of list, leave */
			i5400_printk(KERN_ERR,
				"'system address,Process Bus' "
				"device not found:"
				"vendor 0x%x device 0x%x ERR func 2 "
				"(broken BIOS?)\n",
				PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_5400_ERR);

			pci_dev_put(pvt->branchmap_werrors);
			return -ENODEV;
		}

		/* Store device 16 func 2 */
		if (PCI_FUNC(pdev->devfn) == 2)
			break;
	}
	pvt->fsb_error_regs = pdev;

	edac_dbg(1, "System Address, processor bus- PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->system_address),
		 pvt->system_address->vendor, pvt->system_address->device);
	edac_dbg(1, "Branchmap, control and errors - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->branchmap_werrors),
		 pvt->branchmap_werrors->vendor,
		 pvt->branchmap_werrors->device);
	edac_dbg(1, "FSB Error Regs - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->fsb_error_regs),
		 pvt->fsb_error_regs->vendor, pvt->fsb_error_regs->device);

	pvt->branch_0 = pci_get_device(PCI_VENDOR_ID_INTEL,
				       PCI_DEVICE_ID_INTEL_5400_FBD0, NULL);
	if (!pvt->branch_0) {
		i5400_printk(KERN_ERR,
			"MC: 'BRANCH 0' device not found:"
			"vendor 0x%x device 0x%x Func 0 (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_5400_FBD0);

		pci_dev_put(pvt->fsb_error_regs);
		pci_dev_put(pvt->branchmap_werrors);
		return -ENODEV;
	}

	/* If this device claims to have more than 2 channels then
	 * fetch Branch 1's information
	 */
	if (pvt->maxch < CHANNELS_PER_BRANCH)
		return 0;

	pvt->branch_1 = pci_get_device(PCI_VENDOR_ID_INTEL,
				       PCI_DEVICE_ID_INTEL_5400_FBD1, NULL);
	if (!pvt->branch_1) {
		i5400_printk(KERN_ERR,
			"MC: 'BRANCH 1' device not found:"
			"vendor 0x%x device 0x%x Func 0 "
			"(broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_5400_FBD1);

		pci_dev_put(pvt->branch_0);
		pci_dev_put(pvt->fsb_error_regs);
		pci_dev_put(pvt->branchmap_werrors);
		return -ENODEV;
	}

	return 0;
}