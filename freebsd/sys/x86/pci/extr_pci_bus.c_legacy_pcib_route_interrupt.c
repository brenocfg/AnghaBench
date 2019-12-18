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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_INVALID_IRQ ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int pci_pir_route_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
legacy_pcib_route_interrupt(device_t pcib, device_t dev, int pin)
{

#ifdef __HAVE_PIR
	return (pci_pir_route_interrupt(pci_get_bus(dev), pci_get_slot(dev),
	    pci_get_function(dev), pin));
#else
	/* No routing possible */
	return (PCI_INVALID_IRQ);
#endif
}