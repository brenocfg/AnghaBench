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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct pci_host_bridge {struct pci_bus* bus; int /*<<< orphan*/  map_irq; int /*<<< orphan*/  swizzle_irq; int /*<<< orphan*/  ops; scalar_t__ busnr; struct leon_pci_info* sysdata; TYPE_1__ dev; int /*<<< orphan*/  windows; } ;
struct pci_bus {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ start; } ;
struct leon_pci_info {int /*<<< orphan*/  map_irq; int /*<<< orphan*/  ops; TYPE_3__ busn; TYPE_3__ mem_space; TYPE_2__ io_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_BUS ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_add_resource (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pci_add_resource_offset (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 struct pci_host_bridge* pci_alloc_host_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_assign_unassigned_resources () ; 
 int /*<<< orphan*/  pci_bus_add_devices (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_common_swizzle ; 
 int /*<<< orphan*/  pci_free_host_bridge (struct pci_host_bridge*) ; 
 int pci_scan_root_bus_bridge (struct pci_host_bridge*) ; 
 int /*<<< orphan*/  resources ; 

void leon_pci_init(struct platform_device *ofdev, struct leon_pci_info *info)
{
	LIST_HEAD(resources);
	struct pci_bus *root_bus;
	struct pci_host_bridge *bridge;
	int ret;

	bridge = pci_alloc_host_bridge(0);
	if (!bridge)
		return;

	pci_add_resource_offset(&resources, &info->io_space,
				info->io_space.start - 0x1000);
	pci_add_resource(&resources, &info->mem_space);
	info->busn.flags = IORESOURCE_BUS;
	pci_add_resource(&resources, &info->busn);

	list_splice_init(&resources, &bridge->windows);
	bridge->dev.parent = &ofdev->dev;
	bridge->sysdata = info;
	bridge->busnr = 0;
	bridge->ops = info->ops;
	bridge->swizzle_irq = pci_common_swizzle;
	bridge->map_irq = info->map_irq;

	ret = pci_scan_root_bus_bridge(bridge);
	if (ret) {
		pci_free_host_bridge(bridge);
		return;
	}

	root_bus = bridge->bus;

	/* Assign devices with resources */
	pci_assign_unassigned_resources();
	pci_bus_add_devices(root_bus);
}