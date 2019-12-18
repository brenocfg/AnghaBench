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
typedef  int u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  vendor; } ;
struct bcma_bus {int host_is_pcie2; int /*<<< orphan*/  mmio; struct pci_dev* host_pci; TYPE_2__ boardinfo; int /*<<< orphan*/ * ops; int /*<<< orphan*/  hosttype; int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCIE2 ; 
 int /*<<< orphan*/  BCMA_HOSTTYPE_PCI ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bcma_bus_register (struct bcma_bus*) ; 
 int bcma_bus_scan (struct bcma_bus*) ; 
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*) ; 
 scalar_t__ bcma_find_core (struct bcma_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_host_pci_ops ; 
 int /*<<< orphan*/  bcma_init_bus (struct bcma_bus*) ; 
 int /*<<< orphan*/  bcma_unregister_cores (struct bcma_bus*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bcma_bus*) ; 
 struct bcma_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char const*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct bcma_bus*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static int bcma_host_pci_probe(struct pci_dev *dev,
			       const struct pci_device_id *id)
{
	struct bcma_bus *bus;
	int err = -ENOMEM;
	const char *name;
	u32 val;

	/* Alloc */
	bus = kzalloc(sizeof(*bus), GFP_KERNEL);
	if (!bus)
		goto out;

	/* Basic PCI configuration */
	err = pci_enable_device(dev);
	if (err)
		goto err_kfree_bus;

	name = dev_name(&dev->dev);
	if (dev->driver && dev->driver->name)
		name = dev->driver->name;
	err = pci_request_regions(dev, name);
	if (err)
		goto err_pci_disable;
	pci_set_master(dev);

	/* Disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state */
	pci_read_config_dword(dev, 0x40, &val);
	if ((val & 0x0000ff00) != 0)
		pci_write_config_dword(dev, 0x40, val & 0xffff00ff);

	/* SSB needed additional powering up, do we have any AMBA PCI cards? */
	if (!pci_is_pcie(dev)) {
		bcma_err(bus, "PCI card detected, they are not supported.\n");
		err = -ENXIO;
		goto err_pci_release_regions;
	}

	bus->dev = &dev->dev;

	/* Map MMIO */
	err = -ENOMEM;
	bus->mmio = pci_iomap(dev, 0, ~0UL);
	if (!bus->mmio)
		goto err_pci_release_regions;

	/* Host specific */
	bus->host_pci = dev;
	bus->hosttype = BCMA_HOSTTYPE_PCI;
	bus->ops = &bcma_host_pci_ops;

	bus->boardinfo.vendor = bus->host_pci->subsystem_vendor;
	bus->boardinfo.type = bus->host_pci->subsystem_device;

	/* Initialize struct, detect chip */
	bcma_init_bus(bus);

	/* Scan bus to find out generation of PCIe core */
	err = bcma_bus_scan(bus);
	if (err)
		goto err_pci_unmap_mmio;

	if (bcma_find_core(bus, BCMA_CORE_PCIE2))
		bus->host_is_pcie2 = true;

	/* Register */
	err = bcma_bus_register(bus);
	if (err)
		goto err_unregister_cores;

	pci_set_drvdata(dev, bus);

out:
	return err;

err_unregister_cores:
	bcma_unregister_cores(bus);
err_pci_unmap_mmio:
	pci_iounmap(dev, bus->mmio);
err_pci_release_regions:
	pci_release_regions(dev);
err_pci_disable:
	pci_disable_device(dev);
err_kfree_bus:
	kfree(bus);
	return err;
}