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
struct TYPE_4__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; int /*<<< orphan*/  of_node; } ;
struct pci_dev {int devfn; int dma_mask; scalar_t__ irq; int /*<<< orphan*/  rom_base_reg; int /*<<< orphan*/  hdr_type; int /*<<< orphan*/  error_state; int /*<<< orphan*/  current_state; void* revision; void* class; TYPE_1__* bus; TYPE_2__ dev; int /*<<< orphan*/  cfg_size; void* subsystem_device; void* subsystem_vendor; void* device; void* vendor; scalar_t__ needs_freset; scalar_t__ multifunction; } ;
struct pci_bus {int /*<<< orphan*/  bridge; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE_BRIDGE ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE_CARDBUS ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE_NORMAL ; 
 int /*<<< orphan*/  PCI_ROM_ADDRESS ; 
 int /*<<< orphan*/  PCI_ROM_ADDRESS1 ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int /*<<< orphan*/  PCI_UNKNOWN ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* get_int_prop (struct device_node*,char*,int) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_get_device_type (struct device_node*) ; 
 scalar_t__ of_node_is_type (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_pci_parse_addrs (struct device_node*,struct pci_dev*) ; 
 struct pci_dev* pci_alloc_dev (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  pci_cfg_space_size (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 int /*<<< orphan*/  pci_dev_assign_slot (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_device_add (struct pci_dev*,struct pci_bus*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_fixup_device (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_fixup_early ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  set_pcie_hotplug_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  set_pcie_port_type (struct pci_dev*) ; 

struct pci_dev *of_create_pci_dev(struct device_node *node,
				 struct pci_bus *bus, int devfn)
{
	struct pci_dev *dev;

	dev = pci_alloc_dev(bus);
	if (!dev)
		return NULL;

	pr_debug("    create device, devfn: %x, type: %s\n", devfn,
		 of_node_get_device_type(node));

	dev->dev.of_node = of_node_get(node);
	dev->dev.parent = bus->bridge;
	dev->dev.bus = &pci_bus_type;
	dev->devfn = devfn;
	dev->multifunction = 0;		/* maybe a lie? */
	dev->needs_freset = 0;		/* pcie fundamental reset required */
	set_pcie_port_type(dev);

	pci_dev_assign_slot(dev);
	dev->vendor = get_int_prop(node, "vendor-id", 0xffff);
	dev->device = get_int_prop(node, "device-id", 0xffff);
	dev->subsystem_vendor = get_int_prop(node, "subsystem-vendor-id", 0);
	dev->subsystem_device = get_int_prop(node, "subsystem-id", 0);

	dev->cfg_size = pci_cfg_space_size(dev);

	dev_set_name(&dev->dev, "%04x:%02x:%02x.%d", pci_domain_nr(bus),
		dev->bus->number, PCI_SLOT(devfn), PCI_FUNC(devfn));
	dev->class = get_int_prop(node, "class-code", 0);
	dev->revision = get_int_prop(node, "revision-id", 0);

	pr_debug("    class: 0x%x\n", dev->class);
	pr_debug("    revision: 0x%x\n", dev->revision);

	dev->current_state = PCI_UNKNOWN;	/* unknown power state */
	dev->error_state = pci_channel_io_normal;
	dev->dma_mask = 0xffffffff;

	/* Early fixups, before probing the BARs */
	pci_fixup_device(pci_fixup_early, dev);

	if (of_node_is_type(node, "pci") || of_node_is_type(node, "pciex")) {
		/* a PCI-PCI bridge */
		dev->hdr_type = PCI_HEADER_TYPE_BRIDGE;
		dev->rom_base_reg = PCI_ROM_ADDRESS1;
		set_pcie_hotplug_bridge(dev);
	} else if (of_node_is_type(node, "cardbus")) {
		dev->hdr_type = PCI_HEADER_TYPE_CARDBUS;
	} else {
		dev->hdr_type = PCI_HEADER_TYPE_NORMAL;
		dev->rom_base_reg = PCI_ROM_ADDRESS;
		/* Maybe do a default OF mapping here */
		dev->irq = 0;
	}

	of_pci_parse_addrs(node, dev);

	pr_debug("    adding to system ...\n");

	pci_device_add(dev, bus);

	return dev;
}