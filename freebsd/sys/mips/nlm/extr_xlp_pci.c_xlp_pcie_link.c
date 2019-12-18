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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int pci_get_function (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
xlp_pcie_link(device_t pcib, device_t dev)
{
	device_t parent, tmp;

	/* find the lane on which the slot is connected to */
	tmp = dev;
	while (1) {
		parent = device_get_parent(tmp);
		if (parent == NULL || parent == pcib) {
			device_printf(dev, "Cannot find parent bus\n");
			return (-1);
		}
		if (strcmp(device_get_nameunit(parent), "pci0") == 0)
			break;
		tmp = parent;
	}
	return (pci_get_function(tmp));
}