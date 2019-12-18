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
struct solos_card {scalar_t__ fpga_version; scalar_t__ config_regs; scalar_t__ buffers; struct solos_card* dma_bounce; int /*<<< orphan*/  tlet; TYPE_2__* dev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ DMA_SUPPORTED ; 
 scalar_t__ FPGA_MODE ; 
 scalar_t__ IRQ_EN_ADDR ; 
 int /*<<< orphan*/  atm_remove (struct solos_card*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct solos_card*) ; 
 int /*<<< orphan*/  gpio_attr_group ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct solos_card*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct solos_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fpga_remove(struct pci_dev *dev)
{
	struct solos_card *card = pci_get_drvdata(dev);
	
	/* Disable IRQs */
	iowrite32(0, card->config_regs + IRQ_EN_ADDR);

	/* Reset FPGA */
	iowrite32(1, card->config_regs + FPGA_MODE);
	(void)ioread32(card->config_regs + FPGA_MODE); 

	if (card->fpga_version >= DMA_SUPPORTED)
		sysfs_remove_group(&card->dev->dev.kobj, &gpio_attr_group);

	atm_remove(card);

	free_irq(dev->irq, card);
	tasklet_kill(&card->tlet);

	kfree(card->dma_bounce);

	/* Release device from reset */
	iowrite32(0, card->config_regs + FPGA_MODE);
	(void)ioread32(card->config_regs + FPGA_MODE); 

	pci_iounmap(dev, card->buffers);
	pci_iounmap(dev, card->config_regs);

	pci_release_regions(dev);
	pci_disable_device(dev);

	kfree(card);
}