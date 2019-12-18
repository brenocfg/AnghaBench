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
struct pci_dev {int dummy; } ;
struct dw_edma_chip {int dummy; } ;

/* Variables and functions */
 int dw_edma_remove (struct dw_edma_chip*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 struct dw_edma_chip* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,int) ; 

__attribute__((used)) static void dw_edma_pcie_remove(struct pci_dev *pdev)
{
	struct dw_edma_chip *chip = pci_get_drvdata(pdev);
	int err;

	/* Stopping eDMA driver */
	err = dw_edma_remove(chip);
	if (err)
		pci_warn(pdev, "can't remove device properly: %d\n", err);

	/* Freeing IRQs */
	pci_free_irq_vectors(pdev);
}