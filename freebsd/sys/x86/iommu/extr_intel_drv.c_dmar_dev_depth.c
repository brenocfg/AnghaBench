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
typedef  scalar_t__ devclass_t ;

/* Variables and functions */
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

int
dmar_dev_depth(device_t child)
{
	devclass_t pci_class;
	device_t bus, pcib;
	int depth;

	pci_class = devclass_find("pci");
	for (depth = 1; ; depth++) {
		bus = device_get_parent(child);
		pcib = device_get_parent(bus);
		if (device_get_devclass(device_get_parent(pcib)) !=
		    pci_class)
			return (depth);
		child = pcib;
	}
}