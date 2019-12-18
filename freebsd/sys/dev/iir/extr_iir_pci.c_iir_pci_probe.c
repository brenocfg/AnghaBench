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
 scalar_t__ GDT_DEVICE_ID_MAX ; 
 scalar_t__ GDT_DEVICE_ID_MIN ; 
 scalar_t__ GDT_DEVICE_ID_NEWRX ; 
 scalar_t__ GDT_VENDOR_ID ; 
 scalar_t__ INTEL_DEVICE_ID_IIR ; 
 scalar_t__ INTEL_VENDOR_ID_IIR ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iir_pci_probe(device_t dev)
{
    if (pci_get_vendor(dev) == INTEL_VENDOR_ID_IIR &&
        pci_get_device(dev) == INTEL_DEVICE_ID_IIR) {
        device_set_desc(dev, "Intel Integrated RAID Controller");
        return (BUS_PROBE_DEFAULT);
    }
    if (pci_get_vendor(dev) == GDT_VENDOR_ID &&
        ((pci_get_device(dev) >= GDT_DEVICE_ID_MIN &&
        pci_get_device(dev) <= GDT_DEVICE_ID_MAX) ||
        pci_get_device(dev) == GDT_DEVICE_ID_NEWRX)) {
        device_set_desc(dev, "ICP Disk Array Controller");
        return (BUS_PROBE_DEFAULT);
    }
    return (ENXIO);
}