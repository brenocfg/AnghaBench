#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sb1250_bus_dma_mask_exclude {int set; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus_dma_mask; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; TYPE_3__ dev; TYPE_2__* subordinate; TYPE_1__* bus; } ;
struct TYPE_5__ {scalar_t__ number; } ;
struct TYPE_4__ {scalar_t__ number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ PCI_DEVICE_ID_BCM1250_HT ; 
 scalar_t__ PCI_VENDOR_ID_SIBYTE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,...) ; 
 scalar_t__ pci_bus_max_busnr (TYPE_2__*) ; 

__attribute__((used)) static int sb1250_bus_dma_mask(struct pci_dev *dev, void *data)
{
	struct sb1250_bus_dma_mask_exclude *exclude = data;
	bool exclude_this;
	bool ht_bridge;

	exclude_this = exclude->set && (dev->bus->number >= exclude->start &&
					dev->bus->number <= exclude->end);
	ht_bridge = !exclude->set && (dev->vendor == PCI_VENDOR_ID_SIBYTE &&
				      dev->device == PCI_DEVICE_ID_BCM1250_HT);

	if (exclude_this) {
		dev_dbg(&dev->dev, "not disabling DAC for device");
	} else if (ht_bridge) {
		exclude->start = dev->subordinate->number;
		exclude->end = pci_bus_max_busnr(dev->subordinate);
		exclude->set = true;
		dev_dbg(&dev->dev, "not disabling DAC for [bus %02x-%02x]",
			exclude->start, exclude->end);
	} else {
		dev_dbg(&dev->dev, "disabling DAC for device");
		dev->dev.bus_dma_mask = DMA_BIT_MASK(32);
	}

	return 0;
}