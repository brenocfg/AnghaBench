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
struct bcma_bus {scalar_t__ hosttype; int /*<<< orphan*/ * drv_pci; int /*<<< orphan*/  host_is_pcie2; } ;

/* Variables and functions */
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 int /*<<< orphan*/  bcma_core_pci_down (int /*<<< orphan*/ *) ; 

void bcma_host_pci_down(struct bcma_bus *bus)
{
	if (bus->hosttype != BCMA_HOSTTYPE_PCI)
		return;

	if (!bus->host_is_pcie2)
		bcma_core_pci_down(&bus->drv_pci[0]);
}