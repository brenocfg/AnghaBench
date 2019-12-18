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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
piix_probe(device_t dev)
{
	u_int32_t d;

	if (devclass_get_device(devclass_find("acpi"), 0) != NULL)
		return (ENXIO);
	switch (pci_get_devid(dev)) {
	case 0x71138086:
		device_set_desc(dev, "PIIX Timecounter");
		break;
	default:
		return (ENXIO);
	}

	d = pci_read_config(dev, PCIR_COMMAND, 2);
	if (!(d & PCIM_CMD_PORTEN)) {
		device_printf(dev, "PIIX I/O space not mapped\n");
		return (ENXIO);
	}
	return (0);
}