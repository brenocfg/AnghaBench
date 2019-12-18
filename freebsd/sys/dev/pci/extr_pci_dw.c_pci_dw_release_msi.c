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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int intr_release_msi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_msimap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_dw_release_msi(device_t pci, device_t child, int count, int *irqs)
{
	phandle_t msi_parent;
	int rv;

	rv = ofw_bus_msimap(ofw_bus_get_node(pci), pci_get_rid(child),
	    &msi_parent, NULL);
	if (rv != 0)
		return (rv);
	return (intr_release_msi(pci, child, msi_parent, count, irqs));
}