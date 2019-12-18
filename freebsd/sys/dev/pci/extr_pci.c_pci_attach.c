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
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_add_children (int /*<<< orphan*/ ,int,int) ; 
 int pci_attach_common (int /*<<< orphan*/ ) ; 
 int pcib_get_bus (int /*<<< orphan*/ ) ; 
 int pcib_get_domain (int /*<<< orphan*/ ) ; 

int
pci_attach(device_t dev)
{
	int busno, domain, error;

	error = pci_attach_common(dev);
	if (error)
		return (error);

	/*
	 * Since there can be multiple independently numbered PCI
	 * buses on systems with multiple PCI domains, we can't use
	 * the unit number to decide which bus we are probing. We ask
	 * the parent pcib what our domain and bus numbers are.
	 */
	domain = pcib_get_domain(dev);
	busno = pcib_get_bus(dev);
	pci_add_children(dev, domain, busno);
	return (bus_generic_attach(dev));
}