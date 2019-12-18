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
struct zpci_dev {int domain; TYPE_1__* bars; int /*<<< orphan*/  res_name; } ;
struct resource {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {unsigned long size; int map_idx; int val; struct resource* res; scalar_t__ mio_wb; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long IORESOURCE_MEM ; 
 unsigned long IORESOURCE_MEM_64 ; 
 unsigned long IORESOURCE_PREFETCH ; 
 int PCI_BAR_COUNT ; 
 unsigned long ZPCI_ADDR (int) ; 
 int ZPCI_BUS_NR ; 
 struct resource* __alloc_res (struct zpci_dev*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pci_add_resource (struct list_head*,struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int zpci_alloc_iomap (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_free_iomap (struct zpci_dev*,int) ; 
 scalar_t__ zpci_use_mio (struct zpci_dev*) ; 

__attribute__((used)) static int zpci_setup_bus_resources(struct zpci_dev *zdev,
				    struct list_head *resources)
{
	unsigned long addr, size, flags;
	struct resource *res;
	int i, entry;

	snprintf(zdev->res_name, sizeof(zdev->res_name),
		 "PCI Bus %04x:%02x", zdev->domain, ZPCI_BUS_NR);

	for (i = 0; i < PCI_BAR_COUNT; i++) {
		if (!zdev->bars[i].size)
			continue;
		entry = zpci_alloc_iomap(zdev);
		if (entry < 0)
			return entry;
		zdev->bars[i].map_idx = entry;

		/* only MMIO is supported */
		flags = IORESOURCE_MEM;
		if (zdev->bars[i].val & 8)
			flags |= IORESOURCE_PREFETCH;
		if (zdev->bars[i].val & 4)
			flags |= IORESOURCE_MEM_64;

		if (zpci_use_mio(zdev))
			addr = (unsigned long) zdev->bars[i].mio_wb;
		else
			addr = ZPCI_ADDR(entry);
		size = 1UL << zdev->bars[i].size;

		res = __alloc_res(zdev, addr, size, flags);
		if (!res) {
			zpci_free_iomap(zdev, entry);
			return -ENOMEM;
		}
		zdev->bars[i].res = res;
		pci_add_resource(resources, res);
	}

	return 0;
}