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
typedef  scalar_t__ u8 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  dev; int /*<<< orphan*/  vendor; } ;
struct agp_device_ids {scalar_t__ device_id; scalar_t__ chipset_name; } ;
struct agp_bridge_data {int /*<<< orphan*/  mode; scalar_t__ capndx; int /*<<< orphan*/ * driver; struct pci_dev* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ PCI_AGP_STATUS ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP ; 
 int agp_add_bridge (struct agp_bridge_data*) ; 
 struct agp_bridge_data* agp_alloc_bridge () ; 
 struct agp_device_ids* ati_agp_device_ids ; 
 int /*<<< orphan*/  ati_generic_bridge ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct agp_bridge_data*) ; 

__attribute__((used)) static int agp_ati_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct agp_device_ids *devs = ati_agp_device_ids;
	struct agp_bridge_data *bridge;
	u8 cap_ptr;
	int j;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptr)
		return -ENODEV;

	/* probe for known chipsets */
	for (j = 0; devs[j].chipset_name; j++) {
		if (pdev->device == devs[j].device_id)
			goto found;
	}

	dev_err(&pdev->dev, "unsupported Ati chipset [%04x/%04x])\n",
		pdev->vendor, pdev->device);
	return -ENODEV;

found:
	bridge = agp_alloc_bridge();
	if (!bridge)
		return -ENOMEM;

	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	bridge->driver = &ati_generic_bridge;

	dev_info(&pdev->dev, "Ati %s chipset\n", devs[j].chipset_name);

	/* Fill in the mode register */
	pci_read_config_dword(pdev,
			bridge->capndx+PCI_AGP_STATUS,
			&bridge->mode);

	pci_set_drvdata(pdev, bridge);
	return agp_add_bridge(bridge);
}