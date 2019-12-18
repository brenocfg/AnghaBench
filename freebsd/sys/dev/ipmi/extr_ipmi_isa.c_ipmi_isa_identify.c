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
typedef  int uint32_t ;
struct ipmi_get_info {scalar_t__ iface_type; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PCIR_DEVVENDOR ; 
 scalar_t__ SSIF_MODE ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * ipmi_pci_match (int,int) ; 
 scalar_t__ ipmi_smbios_identify (struct ipmi_get_info*) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ipmi_isa_identify(driver_t *driver, device_t parent)
{
	struct ipmi_get_info info;
	uint32_t devid;

	if (ipmi_smbios_identify(&info) && info.iface_type != SSIF_MODE &&
	    device_find_child(parent, "ipmi", -1) == NULL) {
		/*
		 * XXX: Hack alert.  On some broken systems, the IPMI
		 * interface is described via SMBIOS, but the actual
		 * IO resource is in a PCI device BAR, so we have to let
		 * the PCI device attach ipmi instead.  In that case don't
		 * create an isa ipmi device.  For now we hardcode the list
		 * of bus, device, function tuples.
		 */
		devid = pci_cfgregread(0, 4, 2, PCIR_DEVVENDOR, 4);
		if (devid != 0xffffffff &&
		    ipmi_pci_match(devid & 0xffff, devid >> 16) != NULL)
			return;
		BUS_ADD_CHILD(parent, 0, "ipmi", -1);
	}
}