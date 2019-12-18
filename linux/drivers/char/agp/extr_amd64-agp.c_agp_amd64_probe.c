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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  dev; } ;
struct agp_bridge_data {int /*<<< orphan*/  mode; scalar_t__ capndx; struct pci_dev* dev; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ PCI_AGP_STATUS ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP ; 
 scalar_t__ PCI_DEVICE_ID_AMD_8151_0 ; 
 scalar_t__ PCI_VENDOR_ID_AL ; 
 scalar_t__ PCI_VENDOR_ID_AMD ; 
 scalar_t__ PCI_VENDOR_ID_NVIDIA ; 
 int agp_add_bridge (struct agp_bridge_data*) ; 
 struct agp_bridge_data* agp_alloc_bridge () ; 
 scalar_t__ agp_bridges_found ; 
 int /*<<< orphan*/  agp_put_bridge (struct agp_bridge_data*) ; 
 int /*<<< orphan*/  amd8151_init (struct pci_dev*,struct agp_bridge_data*) ; 
 int /*<<< orphan*/  amd_8151_driver ; 
 int cache_nbs (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int nforce3_agp_init (struct pci_dev*) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct agp_bridge_data*) ; 
 int uli_agp_init (struct pci_dev*) ; 

__attribute__((used)) static int agp_amd64_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct agp_bridge_data *bridge;
	u8 cap_ptr;
	int err;

	/* The Highlander principle */
	if (agp_bridges_found)
		return -ENODEV;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptr)
		return -ENODEV;

	/* Could check for AGPv3 here */

	bridge = agp_alloc_bridge();
	if (!bridge)
		return -ENOMEM;

	if (pdev->vendor == PCI_VENDOR_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_8151_0) {
		amd8151_init(pdev, bridge);
	} else {
		dev_info(&pdev->dev, "AGP bridge [%04x/%04x]\n",
			 pdev->vendor, pdev->device);
	}

	bridge->driver = &amd_8151_driver;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	/* Fill in the mode register */
	pci_read_config_dword(pdev, bridge->capndx+PCI_AGP_STATUS, &bridge->mode);

	if (cache_nbs(pdev, cap_ptr) == -1) {
		agp_put_bridge(bridge);
		return -ENODEV;
	}

	if (pdev->vendor == PCI_VENDOR_ID_NVIDIA) {
		int ret = nforce3_agp_init(pdev);
		if (ret) {
			agp_put_bridge(bridge);
			return ret;
		}
	}

	if (pdev->vendor == PCI_VENDOR_ID_AL) {
		int ret = uli_agp_init(pdev);
		if (ret) {
			agp_put_bridge(bridge);
			return ret;
		}
	}

	pci_set_drvdata(pdev, bridge);
	err = agp_add_bridge(bridge);
	if (err < 0)
		return err;

	agp_bridges_found++;
	return 0;
}