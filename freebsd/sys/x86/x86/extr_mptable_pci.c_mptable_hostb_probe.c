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
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mptable_pci_probe_table (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_cfgregopen () ; 
 int /*<<< orphan*/  pcib_get_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mptable_hostb_probe(device_t dev)
{

	if (pci_cfgregopen() == 0)
		return (ENXIO);
	if (mptable_pci_probe_table(pcib_get_bus(dev)) != 0)
		return (ENXIO);
	device_set_desc(dev, "MPTable Host-PCI bridge");
	return (0);
}