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
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int opal_npu_destroy_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opal_npu_map_lpar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_id (struct pci_dev*) ; 
 struct pci_dev* pnv_pci_get_npu_dev (struct pci_dev*,int /*<<< orphan*/ ) ; 

int pnv_npu2_unmap_lpar_dev(struct pci_dev *gpdev)
{
	int ret;
	struct pci_dev *npdev = pnv_pci_get_npu_dev(gpdev, 0);
	struct pci_controller *hose;
	struct pnv_phb *nphb;

	if (!npdev)
		return -ENODEV;

	hose = pci_bus_to_host(npdev->bus);
	nphb = hose->private_data;

	dev_dbg(&gpdev->dev, "destroy context opalid=%llu\n",
			nphb->opal_id);
	ret = opal_npu_destroy_context(nphb->opal_id, 0/*__unused*/,
				       pci_dev_id(gpdev));
	if (ret < 0) {
		dev_err(&gpdev->dev, "Failed to destroy context: %d\n", ret);
		return ret;
	}

	/* Set LPID to 0 anyway, just to be safe */
	dev_dbg(&gpdev->dev, "Map LPAR opalid=%llu lparid=0\n", nphb->opal_id);
	ret = opal_npu_map_lpar(nphb->opal_id, pci_dev_id(gpdev), 0 /*LPID*/,
				0 /* LPCR bits */);
	if (ret)
		dev_err(&gpdev->dev, "Error %d mapping device to LPAR\n", ret);

	return ret;
}