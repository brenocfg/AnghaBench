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
struct pci_dev {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82801BA_10 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82801CA_12 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82801DB_12 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82815_MC ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 void* pci_get_subsys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/ * speedstep_chipset_dev ; 

__attribute__((used)) static unsigned int speedstep_detect_chipset(void)
{
	speedstep_chipset_dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82801DB_12,
			      PCI_ANY_ID, PCI_ANY_ID,
			      NULL);
	if (speedstep_chipset_dev)
		return 4; /* 4-M */

	speedstep_chipset_dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82801CA_12,
			      PCI_ANY_ID, PCI_ANY_ID,
			      NULL);
	if (speedstep_chipset_dev)
		return 3; /* 3-M */


	speedstep_chipset_dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82801BA_10,
			      PCI_ANY_ID, PCI_ANY_ID,
			      NULL);
	if (speedstep_chipset_dev) {
		/* speedstep.c causes lockups on Dell Inspirons 8000 and
		 * 8100 which use a pretty old revision of the 82815
		 * host bridge. Abort on these systems.
		 */
		struct pci_dev *hostbridge;

		hostbridge  = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82815_MC,
			      PCI_ANY_ID, PCI_ANY_ID,
			      NULL);

		if (!hostbridge)
			return 2; /* 2-M */

		if (hostbridge->revision < 5) {
			pr_debug("hostbridge does not support speedstep\n");
			speedstep_chipset_dev = NULL;
			pci_dev_put(hostbridge);
			return 0;
		}

		pci_dev_put(hostbridge);
		return 2; /* 2-M */
	}

	return 0;
}