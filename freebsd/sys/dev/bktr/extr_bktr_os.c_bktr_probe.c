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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BKTR_PCI_PRODUCT (unsigned int) ; 
 scalar_t__ BKTR_PCI_VENDOR (unsigned int) ; 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
#define  PCI_PRODUCT_BROOKTREE_BT848 131 
#define  PCI_PRODUCT_BROOKTREE_BT849 130 
#define  PCI_PRODUCT_BROOKTREE_BT878 129 
#define  PCI_PRODUCT_BROOKTREE_BT879 128 
 scalar_t__ PCI_VENDOR_BROOKTREE ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 unsigned int pci_get_devid (int /*<<< orphan*/ ) ; 
 unsigned int pci_get_revid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bktr_probe( device_t dev )
{
	unsigned int type = pci_get_devid(dev);
        unsigned int rev  = pci_get_revid(dev);

	if (BKTR_PCI_VENDOR(type) == PCI_VENDOR_BROOKTREE)
	{
		switch (BKTR_PCI_PRODUCT(type)) {
		case PCI_PRODUCT_BROOKTREE_BT848:
			if (rev == 0x12)
				device_set_desc(dev, "BrookTree 848A");
			else
				device_set_desc(dev, "BrookTree 848");
			return BUS_PROBE_DEFAULT;
		case PCI_PRODUCT_BROOKTREE_BT849:
			device_set_desc(dev, "BrookTree 849A");
			return BUS_PROBE_DEFAULT;
		case PCI_PRODUCT_BROOKTREE_BT878:
			device_set_desc(dev, "BrookTree 878");
			return BUS_PROBE_DEFAULT;
		case PCI_PRODUCT_BROOKTREE_BT879:
			device_set_desc(dev, "BrookTree 879");
			return BUS_PROBE_DEFAULT;
		}
	}

        return ENXIO;
}