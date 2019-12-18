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
typedef  int u8 ;
struct pci_dev {TYPE_1__* bus; } ;
struct grpci2_priv {int* irq_map; } ;
struct TYPE_2__ {struct grpci2_priv* sysdata; } ;

/* Variables and functions */

__attribute__((used)) static int grpci2_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	struct grpci2_priv *priv = dev->bus->sysdata;
	int irq_group;

	/* Use default IRQ decoding on PCI BUS0 according slot numbering */
	irq_group = slot & 0x3;
	pin = ((pin - 1) + irq_group) & 0x3;

	return priv->irq_map[pin];
}