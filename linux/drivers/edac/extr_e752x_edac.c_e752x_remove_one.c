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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {scalar_t__ pvt_info; } ;
struct e752x_pvt {int /*<<< orphan*/  dev_d0f1; int /*<<< orphan*/  dev_d0f0; } ;

/* Variables and functions */
 scalar_t__ e752x_pci ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 struct mem_ctl_info* edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_pci_release_generic_ctl (scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e752x_remove_one(struct pci_dev *pdev)
{
	struct mem_ctl_info *mci;
	struct e752x_pvt *pvt;

	edac_dbg(0, "\n");

	if (e752x_pci)
		edac_pci_release_generic_ctl(e752x_pci);

	if ((mci = edac_mc_del_mc(&pdev->dev)) == NULL)
		return;

	pvt = (struct e752x_pvt *)mci->pvt_info;
	pci_dev_put(pvt->dev_d0f0);
	pci_dev_put(pvt->dev_d0f1);
	edac_mc_free(mci);
}