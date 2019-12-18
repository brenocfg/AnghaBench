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
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BUS_FLAGS_NO_AERSID ; 
 scalar_t__ is_vmd (TYPE_1__*) ; 
 scalar_t__ pci_is_root_bus (TYPE_1__*) ; 

__attribute__((used)) static void quirk_no_aersid(struct pci_dev *pdev)
{
	/* VMD Domain */
	if (is_vmd(pdev->bus) && pci_is_root_bus(pdev->bus))
		pdev->bus->bus_flags |= PCI_BUS_FLAGS_NO_AERSID;
}