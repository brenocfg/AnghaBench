#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; struct TYPE_5__* parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; } ;
struct bcma_device {TYPE_2__ dev; TYPE_2__* dma_dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  core_index; } ;
struct bcma_bus {int hosttype; TYPE_2__* dev; TYPE_1__* host_pci; int /*<<< orphan*/  num; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
#define  BCMA_HOSTTYPE_PCI 130 
#define  BCMA_HOSTTYPE_SDIO 129 
#define  BCMA_HOSTTYPE_SOC 128 
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_bus_type ; 
 int /*<<< orphan*/  bcma_of_fill_device (TYPE_2__*,struct bcma_device*) ; 
 int /*<<< orphan*/  bcma_release_core_dev ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bcma_prepare_core(struct bcma_bus *bus, struct bcma_device *core)
{
	core->dev.release = bcma_release_core_dev;
	core->dev.bus = &bcma_bus_type;
	dev_set_name(&core->dev, "bcma%d:%d", bus->num, core->core_index);
	core->dev.parent = bus->dev;
	if (bus->dev)
		bcma_of_fill_device(bus->dev, core);

	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		core->dma_dev = bus->dev;
		core->irq = bus->host_pci->irq;
		break;
	case BCMA_HOSTTYPE_SOC:
		if (IS_ENABLED(CONFIG_OF) && bus->dev) {
			core->dma_dev = bus->dev;
		} else {
			core->dev.dma_mask = &core->dev.coherent_dma_mask;
			core->dma_dev = &core->dev;
		}
		break;
	case BCMA_HOSTTYPE_SDIO:
		break;
	}
}