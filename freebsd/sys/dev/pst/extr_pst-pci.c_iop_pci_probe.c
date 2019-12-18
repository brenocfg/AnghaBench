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
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iop_pci_probe(device_t dev)
{
    /* tested with actual hardware kindly donated by Promise */
    if (pci_get_devid(dev) == 0x19628086 && pci_get_subvendor(dev) == 0x105a) {
	device_set_desc(dev, "Promise SuperTrak SX6000 ATA RAID controller");
	return BUS_PROBE_DEFAULT;
    } 

    /* support the older SuperTrak 100 as well */
    if (pci_get_devid(dev) == 0x19608086 && pci_get_subvendor(dev) == 0x105a) {
	device_set_desc(dev, "Promise SuperTrak 100 ATA RAID controller");
	return BUS_PROBE_DEFAULT;
    } 

    return ENXIO;
}