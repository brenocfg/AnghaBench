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
 int PCI_BUSMAX ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qpi_probe_pcib (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qpi_attach(device_t dev)
{
	int bus;

	/*
	 * Each processor socket has a dedicated PCI bus, sometimes
	 * not enumerated by ACPI.  Probe all unattached buses from 0
	 * to 255.
	 */
	for (bus = PCI_BUSMAX; bus >= 0; bus--)
		qpi_probe_pcib(dev, bus);

	return (bus_generic_attach(dev));
}