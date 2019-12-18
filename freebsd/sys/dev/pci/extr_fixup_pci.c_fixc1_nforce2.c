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
 scalar_t__ pci_get_bus (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_function (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_slot (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
fixc1_nforce2(device_t dev)
{
	uint32_t val;

	if (pci_get_bus(dev) == 0 && pci_get_slot(dev) == 0 &&
	    pci_get_function(dev) == 0) {
		val = pci_read_config(dev, 0x6c, 4);
		if (val & 0x000e0000) {
			device_printf(dev, 
			    "correcting nForce2 C1 CPU disconnect hangs\n");
			val &= ~0x000e0000;
			pci_write_config(dev, 0x6c, val, 4);
		}
	}
}