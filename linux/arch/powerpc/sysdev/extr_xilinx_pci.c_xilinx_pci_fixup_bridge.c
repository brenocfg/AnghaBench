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
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* resource; TYPE_2__* bus; scalar_t__ devfn; } ;
struct pci_controller {int /*<<< orphan*/  dn; } ;
struct TYPE_4__ {scalar_t__ self; } ;
struct TYPE_3__ {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int DEVICE_COUNT_RESOURCE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_controller* pci_bus_to_host (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  xilinx_pci_match ; 

__attribute__((used)) static void xilinx_pci_fixup_bridge(struct pci_dev *dev)
{
	struct pci_controller *hose;
	int i;

	if (dev->devfn || dev->bus->self)
		return;

	hose = pci_bus_to_host(dev->bus);
	if (!hose)
		return;

	if (!of_match_node(xilinx_pci_match, hose->dn))
		return;

	/* Hide the PCI host BARs from the kernel as their content doesn't
	 * fit well in the resource management
	 */
	for (i = 0; i < DEVICE_COUNT_RESOURCE; i++) {
		dev->resource[i].start = 0;
		dev->resource[i].end = 0;
		dev->resource[i].flags = 0;
	}

	dev_info(&dev->dev, "Hiding Xilinx plb-pci host bridge resources %s\n",
		 pci_name(dev));
}