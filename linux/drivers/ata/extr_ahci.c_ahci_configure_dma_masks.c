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
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ dma_mask; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int ahci_configure_dma_masks(struct pci_dev *pdev, int using_dac)
{
	const int dma_bits = using_dac ? 64 : 32;
	int rc;

	/*
	 * If the device fixup already set the dma_mask to some non-standard
	 * value, don't extend it here. This happens on STA2X11, for example.
	 *
	 * XXX: manipulating the DMA mask from platform code is completely
	 * bogus, platform code should use dev->bus_dma_mask instead..
	 */
	if (pdev->dma_mask && pdev->dma_mask < DMA_BIT_MASK(32))
		return 0;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(dma_bits));
	if (rc)
		dev_err(&pdev->dev, "DMA enable failed\n");
	return rc;
}