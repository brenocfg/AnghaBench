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
struct resource {int flags; scalar_t__ start; scalar_t__ end; scalar_t__ parent; } ;
struct pci_dev {int /*<<< orphan*/  dev; struct resource* resource; } ;
struct TYPE_2__ {scalar_t__ vgabios_addr; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int IORESOURCE_PCI_FIXED ; 
 int IORESOURCE_ROM_SHADOW ; 
 size_t PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,size_t,struct resource*) ; 
 TYPE_1__ loongson_sysconf ; 
 int /*<<< orphan*/  pci_disable_rom (struct pci_dev*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 scalar_t__ virt_to_phys (void*) ; 

__attribute__((used)) static void pci_fixup_radeon(struct pci_dev *pdev)
{
	struct resource *res = &pdev->resource[PCI_ROM_RESOURCE];

	if (res->start)
		return;

	if (!loongson_sysconf.vgabios_addr)
		return;

	pci_disable_rom(pdev);
	if (res->parent)
		release_resource(res);

	res->start = virt_to_phys((void *) loongson_sysconf.vgabios_addr);
	res->end   = res->start + 256*1024 - 1;
	res->flags = IORESOURCE_MEM | IORESOURCE_ROM_SHADOW |
		     IORESOURCE_PCI_FIXED;

	dev_info(&pdev->dev, "BAR %d: assigned %pR for Radeon ROM\n",
		 PCI_ROM_RESOURCE, res);
}