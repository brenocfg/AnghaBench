#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int bootloader_config_flags; } ;

/* Variables and functions */
 int CVMX_BOOTINFO_CFG_FLAG_PCI_HOST ; 
 int ENXIO ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PCIE ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
octopci_probe(device_t dev)
{
	if (octeon_has_feature(OCTEON_FEATURE_PCIE)) {
		device_set_desc(dev, "Cavium Octeon PCIe bridge");
		return (0);
	}

	/* Check whether we are a PCI host.  */
	if ((cvmx_sysinfo_get()->bootloader_config_flags & CVMX_BOOTINFO_CFG_FLAG_PCI_HOST) == 0)
		return (ENXIO);

	if (device_get_unit(dev) != 0)
		return (ENXIO);

	device_set_desc(dev, "Cavium Octeon PCI bridge");
	return (0);
}