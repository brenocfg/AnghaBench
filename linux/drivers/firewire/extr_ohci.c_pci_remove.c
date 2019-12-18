#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct fw_ohci {scalar_t__ next_config_rom; scalar_t__ config_rom; scalar_t__ misc_buffer; int /*<<< orphan*/  registers; struct fw_ohci* ir_context_list; struct fw_ohci* it_context_list; int /*<<< orphan*/  at_response_ctx; int /*<<< orphan*/  at_request_ctx; int /*<<< orphan*/  misc_buffer_bus; TYPE_1__ card; int /*<<< orphan*/  ar_response_ctx; int /*<<< orphan*/  ar_request_ctx; int /*<<< orphan*/  config_rom_bus; int /*<<< orphan*/  next_config_rom_bus; int /*<<< orphan*/  bus_reset_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ROM_SIZE ; 
 int /*<<< orphan*/  OHCI1394_HCControlSet ; 
 int OHCI1394_HCControl_LPS ; 
 int /*<<< orphan*/  OHCI1394_IntMaskClear ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ar_context_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fw_ohci*) ; 
 int /*<<< orphan*/  fw_core_remove_card (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct fw_ohci*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct fw_ohci* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_ohci_off (struct pci_dev*) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  software_reset (struct fw_ohci*) ; 

__attribute__((used)) static void pci_remove(struct pci_dev *dev)
{
	struct fw_ohci *ohci = pci_get_drvdata(dev);

	/*
	 * If the removal is happening from the suspend state, LPS won't be
	 * enabled and host registers (eg., IntMaskClear) won't be accessible.
	 */
	if (reg_read(ohci, OHCI1394_HCControlSet) & OHCI1394_HCControl_LPS) {
		reg_write(ohci, OHCI1394_IntMaskClear, ~0);
		flush_writes(ohci);
	}
	cancel_work_sync(&ohci->bus_reset_work);
	fw_core_remove_card(&ohci->card);

	/*
	 * FIXME: Fail all pending packets here, now that the upper
	 * layers can't queue any more.
	 */

	software_reset(ohci);
	free_irq(dev->irq, ohci);

	if (ohci->next_config_rom && ohci->next_config_rom != ohci->config_rom)
		dma_free_coherent(ohci->card.device, CONFIG_ROM_SIZE,
				  ohci->next_config_rom, ohci->next_config_rom_bus);
	if (ohci->config_rom)
		dma_free_coherent(ohci->card.device, CONFIG_ROM_SIZE,
				  ohci->config_rom, ohci->config_rom_bus);
	ar_context_release(&ohci->ar_request_ctx);
	ar_context_release(&ohci->ar_response_ctx);
	dma_free_coherent(ohci->card.device, PAGE_SIZE,
			  ohci->misc_buffer, ohci->misc_buffer_bus);
	context_release(&ohci->at_request_ctx);
	context_release(&ohci->at_response_ctx);
	kfree(ohci->it_context_list);
	kfree(ohci->ir_context_list);
	pci_disable_msi(dev);
	pci_iounmap(dev, ohci->registers);
	pci_release_region(dev, 0);
	pci_disable_device(dev);
	kfree(ohci);
	pmac_ohci_off(dev);

	dev_notice(&dev->dev, "removed fw-ohci device\n");
}