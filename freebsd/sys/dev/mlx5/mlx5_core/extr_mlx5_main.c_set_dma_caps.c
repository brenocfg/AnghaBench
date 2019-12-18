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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_dma_caps(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev = pci_get_drvdata(pdev);
	int err;

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	if (err) {
		mlx5_core_warn(dev, "couldn't set 64-bit PCI DMA mask\n");
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err) {
			mlx5_core_err(dev, "Can't set PCI DMA mask, aborting\n");
			return err;
		}
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	if (err) {
		mlx5_core_warn(dev, "couldn't set 64-bit consistent PCI DMA mask\n");
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err) {
			mlx5_core_err(dev, "Can't set consistent PCI DMA mask, aborting\n");
			return err;
		}
	}

	dma_set_max_seg_size(&pdev->dev, 2u * 1024 * 1024 * 1024);
	return err;
}