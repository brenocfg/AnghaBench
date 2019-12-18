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
struct i82875p_pvt {scalar_t__ ovrfl_pdev; scalar_t__ ovrfl_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 struct mem_ctl_info* edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_pci_release_generic_ctl (scalar_t__) ; 
 scalar_t__ i82875p_pci ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (scalar_t__) ; 

__attribute__((used)) static void i82875p_remove_one(struct pci_dev *pdev)
{
	struct mem_ctl_info *mci;
	struct i82875p_pvt *pvt = NULL;

	edac_dbg(0, "\n");

	if (i82875p_pci)
		edac_pci_release_generic_ctl(i82875p_pci);

	if ((mci = edac_mc_del_mc(&pdev->dev)) == NULL)
		return;

	pvt = (struct i82875p_pvt *)mci->pvt_info;

	if (pvt->ovrfl_window)
		iounmap(pvt->ovrfl_window);

	if (pvt->ovrfl_pdev) {
#ifdef CORRECT_BIOS
		pci_release_regions(pvt->ovrfl_pdev);
#endif				/*CORRECT_BIOS */
		pci_disable_device(pvt->ovrfl_pdev);
		pci_dev_put(pvt->ovrfl_pdev);
	}

	edac_mc_free(mci);
}