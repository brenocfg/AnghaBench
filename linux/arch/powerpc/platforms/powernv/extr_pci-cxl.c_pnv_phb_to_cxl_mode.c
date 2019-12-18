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
typedef  int /*<<< orphan*/  uint64_t ;
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct pnv_ioda_pe {int /*<<< orphan*/  pe_number; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int OPAL_UNSUPPORTED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int opal_pci_set_phb_cxl_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_info (struct pnv_ioda_pe*,char*) ; 
 struct pnv_ioda_pe* pnv_ioda_get_pe (struct pci_dev*) ; 

int pnv_phb_to_cxl_mode(struct pci_dev *dev, uint64_t mode)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	struct pnv_phb *phb = hose->private_data;
	struct pnv_ioda_pe *pe;
	int rc;

	pe = pnv_ioda_get_pe(dev);
	if (!pe)
		return -ENODEV;

	pe_info(pe, "Switching PHB to CXL\n");

	rc = opal_pci_set_phb_cxl_mode(phb->opal_id, mode, pe->pe_number);
	if (rc == OPAL_UNSUPPORTED)
		dev_err(&dev->dev, "Required cxl mode not supported by firmware - update skiboot\n");
	else if (rc)
		dev_err(&dev->dev, "opal_pci_set_phb_cxl_mode failed: %i\n", rc);

	return rc;
}