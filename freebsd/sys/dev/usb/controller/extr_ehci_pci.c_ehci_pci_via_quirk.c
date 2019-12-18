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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
ehci_pci_via_quirk(device_t self)
{
	uint32_t val;

	if ((pci_get_device(self) == 0x3104) && 
	    ((pci_get_revid(self) & 0xf0) == 0x60)) {
		/* Correct schedule sleep time to 10us */
		val = pci_read_config(self, 0x4b, 1);
		if (val & 0x20)
			return;
		val |= 0x20;
		pci_write_config(self, 0x4b, val, 1);
		device_printf(self, "VIA-quirk applied\n");
	}
}