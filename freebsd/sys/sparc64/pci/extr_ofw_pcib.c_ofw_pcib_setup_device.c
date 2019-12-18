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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFW_PCI_SETUP_DEVICE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PCI_VENDOR_PLX 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ofw_pcib_setup_device(device_t bus, device_t child)
{
	int i;
	uint16_t reg;

	switch (pci_get_vendor(bus)) {
	/*
	 * For PLX PEX 8532 issue 64 TLPs to the child from the downstream
	 * port to the child device in order to work around a hardware bug.
	 */
	case PCI_VENDOR_PLX:
		for (i = 0, reg = 0; i < 64; i++)
			reg |= pci_get_devid(child);
		break;
	}

	OFW_PCI_SETUP_DEVICE(device_get_parent(bus), child);
}