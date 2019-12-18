#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sta2x11_instance {int dummy; } ;
struct TYPE_3__ {int is_sta2x11; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;

/* Variables and functions */
 scalar_t__ STA2X11_AMBA_SIZE ; 
 int /*<<< orphan*/  pci_set_consistent_dma_mask (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_set_dma_mask (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 struct sta2x11_instance* sta2x11_pdev_to_instance (struct pci_dev*) ; 

__attribute__((used)) static void sta2x11_setup_pdev(struct pci_dev *pdev)
{
	struct sta2x11_instance *instance = sta2x11_pdev_to_instance(pdev);

	if (!instance) /* either a sta2x11 bridge or another ST device */
		return;
	pci_set_consistent_dma_mask(pdev, STA2X11_AMBA_SIZE - 1);
	pci_set_dma_mask(pdev, STA2X11_AMBA_SIZE - 1);
	pdev->dev.archdata.is_sta2x11 = true;

	/* We must enable all devices as master, for audio DMA to work */
	pci_set_master(pdev);
}