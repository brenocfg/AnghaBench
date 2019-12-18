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
typedef  int u16 ;
struct resource {int start; int end; int flags; scalar_t__ parent; } ;
struct pci_dev {int /*<<< orphan*/  dev; struct resource* resource; struct pci_bus* bus; } ;
struct pci_bus {struct pci_bus* parent; struct pci_dev* self; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int IORESOURCE_PCI_FIXED ; 
 int IORESOURCE_ROM_SHADOW ; 
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int PCI_BRIDGE_CTL_VGA ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
 size_t PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct resource*) ; 
 scalar_t__ is_uv_system () ; 
 int /*<<< orphan*/  pci_disable_rom (struct pci_dev*) ; 
 scalar_t__ pci_is_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 
 struct pci_dev* vga_default_device () ; 

__attribute__((used)) static void pci_fixup_video(struct pci_dev *pdev)
{
	struct pci_dev *bridge;
	struct pci_bus *bus;
	u16 config;
	struct resource *res;

	if (is_uv_system())
		return;
	/* Maybe, this machine supports legacy memory map. */

	/* Is VGA routed to us? */
	bus = pdev->bus;
	while (bus) {
		bridge = bus->self;

		/*
		 * From information provided by
		 * "David Miller" <davem@davemloft.net>
		 * The bridge control register is valid for PCI header
		 * type BRIDGE, or CARDBUS. Host to PCI controllers use
		 * PCI header type NORMAL.
		 */
		if (bridge && (pci_is_bridge(bridge))) {
			pci_read_config_word(bridge, PCI_BRIDGE_CONTROL,
						&config);
			if (!(config & PCI_BRIDGE_CTL_VGA))
				return;
		}
		bus = bus->parent;
	}
	if (!vga_default_device() || pdev == vga_default_device()) {
		pci_read_config_word(pdev, PCI_COMMAND, &config);
		if (config & (PCI_COMMAND_IO | PCI_COMMAND_MEMORY)) {
			res = &pdev->resource[PCI_ROM_RESOURCE];

			pci_disable_rom(pdev);
			if (res->parent)
				release_resource(res);

			res->start = 0xC0000;
			res->end = res->start + 0x20000 - 1;
			res->flags = IORESOURCE_MEM | IORESOURCE_ROM_SHADOW |
				     IORESOURCE_PCI_FIXED;
			dev_info(&pdev->dev, "Video device with shadowed ROM at %pR\n",
				 res);
		}
	}
}