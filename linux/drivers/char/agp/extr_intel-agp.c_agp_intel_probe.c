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
typedef  scalar_t__ u8 ;
struct resource {scalar_t__ end; int /*<<< orphan*/  start; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  dev; struct resource* resource; int /*<<< orphan*/  vendor; } ;
struct agp_bridge_data {int /*<<< orphan*/  mode; scalar_t__ capndx; int /*<<< orphan*/ * dev_private_data; struct pci_dev* dev; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {scalar_t__ chip_id; int /*<<< orphan*/ * name; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ PCI_AGP_STATUS ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP ; 
 int agp_add_bridge (struct agp_bridge_data*) ; 
 struct agp_bridge_data* agp_alloc_bridge () ; 
 int /*<<< orphan*/  agp_put_bridge (struct agp_bridge_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* intel_agp_chipsets ; 
 scalar_t__ intel_gmch_probe (struct pci_dev*,int /*<<< orphan*/ *,struct agp_bridge_data*) ; 
 scalar_t__ pci_assign_resource (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct agp_bridge_data*) ; 

__attribute__((used)) static int agp_intel_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct agp_bridge_data *bridge;
	u8 cap_ptr = 0;
	struct resource *r;
	int i, err;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);

	bridge = agp_alloc_bridge();
	if (!bridge)
		return -ENOMEM;

	bridge->capndx = cap_ptr;

	if (intel_gmch_probe(pdev, NULL, bridge))
		goto found_gmch;

	for (i = 0; intel_agp_chipsets[i].name != NULL; i++) {
		/* In case that multiple models of gfx chip may
		   stand on same host bridge type, this can be
		   sure we detect the right IGD. */
		if (pdev->device == intel_agp_chipsets[i].chip_id) {
			bridge->driver = intel_agp_chipsets[i].driver;
			break;
		}
	}

	if (!bridge->driver) {
		if (cap_ptr)
			dev_warn(&pdev->dev, "unsupported Intel chipset [%04x/%04x]\n",
				 pdev->vendor, pdev->device);
		agp_put_bridge(bridge);
		return -ENODEV;
	}

	bridge->dev = pdev;
	bridge->dev_private_data = NULL;

	dev_info(&pdev->dev, "Intel %s Chipset\n", intel_agp_chipsets[i].name);

	/*
	* The following fixes the case where the BIOS has "forgotten" to
	* provide an address range for the GART.
	* 20030610 - hamish@zot.org
	* This happens before pci_enable_device() intentionally;
	* calling pci_enable_device() before assigning the resource
	* will result in the GART being disabled on machines with such
	* BIOSs (the GART ends up with a BAR starting at 0, which
	* conflicts a lot of other devices).
	*/
	r = &pdev->resource[0];
	if (!r->start && r->end) {
		if (pci_assign_resource(pdev, 0)) {
			dev_err(&pdev->dev, "can't assign resource 0\n");
			agp_put_bridge(bridge);
			return -ENODEV;
		}
	}

	/*
	* If the device has not been properly setup, the following will catch
	* the problem and should stop the system from crashing.
	* 20030610 - hamish@zot.org
	*/
	if (pci_enable_device(pdev)) {
		dev_err(&pdev->dev, "can't enable PCI device\n");
		agp_put_bridge(bridge);
		return -ENODEV;
	}

	/* Fill in the mode register */
	if (cap_ptr) {
		pci_read_config_dword(pdev,
				bridge->capndx+PCI_AGP_STATUS,
				&bridge->mode);
	}

found_gmch:
	pci_set_drvdata(pdev, bridge);
	err = agp_add_bridge(bridge);
	return err;
}