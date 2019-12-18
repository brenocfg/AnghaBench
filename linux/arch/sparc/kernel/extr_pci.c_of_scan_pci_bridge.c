#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct resource {int flags; } ;
struct pci_pbm_info {int dummy; } ;
struct pci_dev {TYPE_1__* bus; struct resource* resource; } ;
struct pci_bus_region {int start; int end; } ;
struct pci_bus {int number; struct device_node* name; struct resource** resource; scalar_t__ bridge_ctl; int /*<<< orphan*/  primary; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int GET_64BIT (int /*<<< orphan*/  const*,int) ; 
 unsigned int IORESOURCE_IO ; 
 size_t PCI_BRIDGE_RESOURCES ; 
 size_t PCI_NUM_RESOURCES ; 
 int /*<<< orphan*/  apb_fake_ranges (struct pci_dev*,struct pci_bus*,struct pci_pbm_info*) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 scalar_t__ ofpci_verbose ; 
 struct pci_bus* pci_add_new_bus (TYPE_1__*,struct pci_dev*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pci_bus_insert_busn_res (struct pci_bus*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,struct device_node*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  pci_of_scan_bus (struct pci_pbm_info*,struct device_node*,struct pci_bus*) ; 
 unsigned int pci_parse_of_flags (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pci_read_bridge_bases (struct pci_bus*) ; 
 int /*<<< orphan*/  pcibios_bus_to_resource (TYPE_1__*,struct resource*,struct pci_bus_region*) ; 
 int /*<<< orphan*/  sprintf (struct device_node*,char*,int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void of_scan_pci_bridge(struct pci_pbm_info *pbm,
			       struct device_node *node,
			       struct pci_dev *dev)
{
	struct pci_bus *bus;
	const u32 *busrange, *ranges;
	int len, i, simba;
	struct pci_bus_region region;
	struct resource *res;
	unsigned int flags;
	u64 size;

	if (ofpci_verbose)
		pci_info(dev, "of_scan_pci_bridge(%pOF)\n", node);

	/* parse bus-range property */
	busrange = of_get_property(node, "bus-range", &len);
	if (busrange == NULL || len != 8) {
		pci_info(dev, "Can't get bus-range for PCI-PCI bridge %pOF\n",
		       node);
		return;
	}

	if (ofpci_verbose)
		pci_info(dev, "    Bridge bus range [%u --> %u]\n",
			 busrange[0], busrange[1]);

	ranges = of_get_property(node, "ranges", &len);
	simba = 0;
	if (ranges == NULL) {
		const char *model = of_get_property(node, "model", NULL);
		if (model && !strcmp(model, "SUNW,simba"))
			simba = 1;
	}

	bus = pci_add_new_bus(dev->bus, dev, busrange[0]);
	if (!bus) {
		pci_err(dev, "Failed to create pci bus for %pOF\n",
			node);
		return;
	}

	bus->primary = dev->bus->number;
	pci_bus_insert_busn_res(bus, busrange[0], busrange[1]);
	bus->bridge_ctl = 0;

	if (ofpci_verbose)
		pci_info(dev, "    Bridge ranges[%p] simba[%d]\n",
			 ranges, simba);

	/* parse ranges property, or cook one up by hand for Simba */
	/* PCI #address-cells == 3 and #size-cells == 2 always */
	res = &dev->resource[PCI_BRIDGE_RESOURCES];
	for (i = 0; i < PCI_NUM_RESOURCES - PCI_BRIDGE_RESOURCES; ++i) {
		res->flags = 0;
		bus->resource[i] = res;
		++res;
	}
	if (simba) {
		apb_fake_ranges(dev, bus, pbm);
		goto after_ranges;
	} else if (ranges == NULL) {
		pci_read_bridge_bases(bus);
		goto after_ranges;
	}
	i = 1;
	for (; len >= 32; len -= 32, ranges += 8) {
		u64 start;

		if (ofpci_verbose)
			pci_info(dev, "    RAW Range[%08x:%08x:%08x:%08x:%08x:%08x:"
				 "%08x:%08x]\n",
				 ranges[0], ranges[1], ranges[2], ranges[3],
				 ranges[4], ranges[5], ranges[6], ranges[7]);

		flags = pci_parse_of_flags(ranges[0]);
		size = GET_64BIT(ranges, 6);
		if (flags == 0 || size == 0)
			continue;

		/* On PCI-Express systems, PCI bridges that have no devices downstream
		 * have a bogus size value where the first 32-bit cell is 0xffffffff.
		 * This results in a bogus range where start + size overflows.
		 *
		 * Just skip these otherwise the kernel will complain when the resource
		 * tries to be claimed.
		 */
		if (size >> 32 == 0xffffffff)
			continue;

		if (flags & IORESOURCE_IO) {
			res = bus->resource[0];
			if (res->flags) {
				pci_err(dev, "ignoring extra I/O range"
					" for bridge %pOF\n", node);
				continue;
			}
		} else {
			if (i >= PCI_NUM_RESOURCES - PCI_BRIDGE_RESOURCES) {
				pci_err(dev, "too many memory ranges"
					" for bridge %pOF\n", node);
				continue;
			}
			res = bus->resource[i];
			++i;
		}

		res->flags = flags;
		region.start = start = GET_64BIT(ranges, 1);
		region.end = region.start + size - 1;

		if (ofpci_verbose)
			pci_info(dev, "      Using flags[%08x] start[%016llx] size[%016llx]\n",
				 flags, start, size);

		pcibios_bus_to_resource(dev->bus, res, &region);
	}
after_ranges:
	sprintf(bus->name, "PCI Bus %04x:%02x", pci_domain_nr(bus),
		bus->number);
	if (ofpci_verbose)
		pci_info(dev, "    bus name: %s\n", bus->name);

	pci_of_scan_bus(pbm, node, bus);
}