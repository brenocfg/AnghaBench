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
struct thunderx_lmc {scalar_t__ regs; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {struct thunderx_lmc* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_INT_ENA_ALL ; 
 scalar_t__ LMC_INT_ENA_W1C ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 struct mem_ctl_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void thunderx_lmc_remove(struct pci_dev *pdev)
{
	struct mem_ctl_info *mci = pci_get_drvdata(pdev);
	struct thunderx_lmc *lmc = mci->pvt_info;

	writeq(LMC_INT_ENA_ALL, lmc->regs + LMC_INT_ENA_W1C);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_free(mci);
}