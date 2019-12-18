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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_LEGSUP ; 
 int /*<<< orphan*/  PCI_LEGSUP_USBPIRQDEN ; 
 int PCI_UHCI_BASE_REG ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  UHCI_INTR ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_write_2 (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uhci_early_takeover(device_t self)
{
	struct resource *res;
	int rid;

	/*
	 * Set the PIRQD enable bit and switch off all the others. We don't
	 * want legacy support to interfere with us XXX Does this also mean
	 * that the BIOS won't touch the keyboard anymore if it is connected
	 * to the ports of the root hub?
	 */
	pci_write_config(self, PCI_LEGSUP, PCI_LEGSUP_USBPIRQDEN, 2);

	/* Disable interrupts */
	rid = PCI_UHCI_BASE_REG;
	res = bus_alloc_resource_any(self, SYS_RES_IOPORT, &rid, RF_ACTIVE);
	if (res != NULL) {
		bus_write_2(res, UHCI_INTR, 0);
		bus_release_resource(self, SYS_RES_IOPORT, rid, res);
	}
}