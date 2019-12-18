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
 scalar_t__ IPS_COPPERHEAD_DEVICE_ID ; 
 scalar_t__ IPS_MARCO_DEVICE_ID ; 
 scalar_t__ IPS_MORPHEUS_DEVICE_ID ; 
 scalar_t__ IPS_VENDOR_ID ; 
 scalar_t__ IPS_VENDOR_ID_ADAPTEC ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ips_pci_probe(device_t dev)
{

        if ((pci_get_vendor(dev) == IPS_VENDOR_ID) &&
	    (pci_get_device(dev) == IPS_MORPHEUS_DEVICE_ID)) {
		device_set_desc(dev, "IBM ServeRAID Adapter");
                return (BUS_PROBE_DEFAULT);
        } else if ((pci_get_vendor(dev) == IPS_VENDOR_ID) &&
	    (pci_get_device(dev) == IPS_COPPERHEAD_DEVICE_ID)) {
		device_set_desc(dev, "IBM ServeRAID Adapter");
		return (BUS_PROBE_DEFAULT);
        } else if ((pci_get_vendor(dev) == IPS_VENDOR_ID_ADAPTEC) &&
	    (pci_get_device(dev) == IPS_MARCO_DEVICE_ID)) {
		device_set_desc(dev, "Adaptec ServeRAID Adapter");
		return (BUS_PROBE_DEFAULT);
	}
        return(ENXIO);
}