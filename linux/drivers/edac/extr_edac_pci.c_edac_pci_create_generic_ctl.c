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
struct edac_pci_gen_data {scalar_t__ edac_idx; } ;
struct edac_pci_ctl_info {char const* mod_name; int /*<<< orphan*/  edac_check; int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  dev_name; struct device* dev; struct edac_pci_gen_data* pvt_info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EDAC_OPSTATE_POLL ; 
 int /*<<< orphan*/  EDAC_PCI_GENCTL_NAME ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct edac_pci_ctl_info*) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 scalar_t__ edac_op_state ; 
 scalar_t__ edac_pci_add_device (struct edac_pci_ctl_info*,scalar_t__) ; 
 struct edac_pci_ctl_info* edac_pci_alloc_ctl_info (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_pci_free_ctl_info (struct edac_pci_ctl_info*) ; 
 int /*<<< orphan*/  edac_pci_generic_check ; 
 int /*<<< orphan*/  edac_pci_idx ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

struct edac_pci_ctl_info *edac_pci_create_generic_ctl(struct device *dev,
						const char *mod_name)
{
	struct edac_pci_ctl_info *pci;
	struct edac_pci_gen_data *pdata;

	pci = edac_pci_alloc_ctl_info(sizeof(*pdata), EDAC_PCI_GENCTL_NAME);
	if (!pci)
		return NULL;

	pdata = pci->pvt_info;
	pci->dev = dev;
	dev_set_drvdata(pci->dev, pci);
	pci->dev_name = pci_name(to_pci_dev(dev));

	pci->mod_name = mod_name;
	pci->ctl_name = EDAC_PCI_GENCTL_NAME;
	if (edac_op_state == EDAC_OPSTATE_POLL)
		pci->edac_check = edac_pci_generic_check;

	pdata->edac_idx = edac_pci_idx++;

	if (edac_pci_add_device(pci, pdata->edac_idx) > 0) {
		edac_dbg(3, "failed edac_pci_add_device()\n");
		edac_pci_free_ctl_info(pci);
		return NULL;
	}

	return pci;
}