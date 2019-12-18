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
struct bcma_device {struct bcma_bus* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  core; } ;
struct bcma_bus {int hosttype; int /*<<< orphan*/  dev; TYPE_2__ drv_mips; TYPE_1__* host_pci; } ;
struct TYPE_3__ {unsigned int irq; } ;

/* Variables and functions */
#define  BCMA_HOSTTYPE_PCI 130 
#define  BCMA_HOSTTYPE_SDIO 129 
#define  BCMA_HOSTTYPE_SOC 128 
 unsigned int bcma_core_mips_irq (struct bcma_device*) ; 
 unsigned int bcma_of_get_irq (int /*<<< orphan*/ ,struct bcma_device*,int) ; 

unsigned int bcma_core_irq(struct bcma_device *core, int num)
{
	struct bcma_bus *bus = core->bus;
	unsigned int mips_irq;

	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		return bus->host_pci->irq;
	case BCMA_HOSTTYPE_SOC:
		if (bus->drv_mips.core && num == 0) {
			mips_irq = bcma_core_mips_irq(core);
			return mips_irq <= 4 ? mips_irq + 2 : 0;
		}
		if (bus->dev)
			return bcma_of_get_irq(bus->dev, core, num);
		return 0;
	case BCMA_HOSTTYPE_SDIO:
		return 0;
	}

	return 0;
}