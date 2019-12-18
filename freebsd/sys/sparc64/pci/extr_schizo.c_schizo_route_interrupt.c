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
typedef  int ofw_pci_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INTERRUPT_VALID (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofw_pci_route_interrupt_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
schizo_route_interrupt(device_t bridge, device_t dev, int pin)
{
	ofw_pci_intr_t mintr;

	mintr = ofw_pci_route_interrupt_common(bridge, dev, pin);
	if (!PCI_INTERRUPT_VALID(mintr))
		device_printf(bridge,
		    "could not route pin %d for device %d.%d\n",
		    pin, pci_get_slot(dev), pci_get_function(dev));
	return (mintr);
}