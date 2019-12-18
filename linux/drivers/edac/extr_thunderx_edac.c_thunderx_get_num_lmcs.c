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
struct TYPE_2__ {unsigned int numa_node; } ;
struct pci_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID_THUNDER_LMC ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_CAVIUM ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 

__attribute__((used)) static unsigned int thunderx_get_num_lmcs(unsigned int node)
{
	unsigned int number = 0;
	struct pci_dev *pdev = NULL;

	do {
		pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
				      PCI_DEVICE_ID_THUNDER_LMC,
				      pdev);
		if (pdev) {
#ifdef CONFIG_NUMA
			if (pdev->dev.numa_node == node)
				number++;
#else
			number++;
#endif
		}
	} while (pdev);

	return number;
}