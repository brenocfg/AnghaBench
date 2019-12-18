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
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int bridge_ctl; } ;

/* Variables and functions */
 int PCI_BRIDGE_CTL_ISA ; 
 int /*<<< orphan*/  PCI_CAN_SKIP_ISA_ALIGN ; 
 scalar_t__ pci_has_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skip_isa_ioresource_align(struct pci_dev *dev)
{
	if (pci_has_flag(PCI_CAN_SKIP_ISA_ALIGN) &&
	    !(dev->bus->bridge_ctl & PCI_BRIDGE_CTL_ISA))
		return 1;
	return 0;
}