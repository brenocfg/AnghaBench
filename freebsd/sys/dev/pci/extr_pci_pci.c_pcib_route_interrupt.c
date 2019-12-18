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
 int PCIB_ROUTE_INTERRUPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCI_INTERRUPT_VALID (int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,char,int) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 

int
pcib_route_interrupt(device_t pcib, device_t dev, int pin)
{
    device_t	bus;
    int		parent_intpin;
    int		intnum;

    /*
     *
     * The PCI standard defines a swizzle of the child-side device/intpin to
     * the parent-side intpin as follows.
     *
     * device = device on child bus
     * child_intpin = intpin on child bus slot (0-3)
     * parent_intpin = intpin on parent bus slot (0-3)
     *
     * parent_intpin = (device + child_intpin) % 4
     */
    parent_intpin = (pci_get_slot(dev) + (pin - 1)) % 4;

    /*
     * Our parent is a PCI bus.  Its parent must export the pcib interface
     * which includes the ability to route interrupts.
     */
    bus = device_get_parent(pcib);
    intnum = PCIB_ROUTE_INTERRUPT(device_get_parent(bus), pcib, parent_intpin + 1);
    if (PCI_INTERRUPT_VALID(intnum) && bootverbose) {
	device_printf(pcib, "slot %d INT%c is routed to irq %d\n",
	    pci_get_slot(dev), 'A' + pin - 1, intnum);
    }
    return(intnum);
}