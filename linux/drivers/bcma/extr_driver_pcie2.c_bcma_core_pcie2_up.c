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
struct pci_dev {int dummy; } ;
struct bcma_drv_pcie2 {int /*<<< orphan*/  reqsize; TYPE_1__* core; } ;
struct bcma_bus {struct pci_dev* host_pci; } ;
struct TYPE_2__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*,int) ; 
 int pcie_set_readrq (struct pci_dev*,int /*<<< orphan*/ ) ; 

void bcma_core_pcie2_up(struct bcma_drv_pcie2 *pcie2)
{
	struct bcma_bus *bus = pcie2->core->bus;
	struct pci_dev *dev = bus->host_pci;
	int err;

	err = pcie_set_readrq(dev, pcie2->reqsize);
	if (err)
		bcma_err(bus, "Error setting PCI_EXP_DEVCTL_READRQ: %d\n", err);
}