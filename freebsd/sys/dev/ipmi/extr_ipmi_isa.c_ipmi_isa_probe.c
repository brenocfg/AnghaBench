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
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ipmi_attached ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipmi_isa_probe(device_t dev)
{

	/*
	 * Give other drivers precedence.  Unfortunately, this doesn't
	 * work if we have an SMBIOS table that duplicates a PCI device
	 * that's later on the bus than the PCI-ISA bridge.
	 */
	if (ipmi_attached)
		return (ENXIO);

	/* Skip any PNP devices. */
	if (isa_get_logicalid(dev) != 0)
		return (ENXIO);

	device_set_desc(dev, "IPMI System Interface");
	return (BUS_PROBE_DEFAULT);
}