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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int /*<<< orphan*/  PCI_CBMEM ; 
 scalar_t__ PCI_POWERSTATE_D0 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ohci_pci_take_controller(device_t self)
{
	uint32_t reg;
	uint32_t int_line;

	if (pci_get_powerstate(self) != PCI_POWERSTATE_D0) {
		device_printf(self, "chip is in D%d mode "
		    "-- setting to D0\n", pci_get_powerstate(self));
		reg = pci_read_config(self, PCI_CBMEM, 4);
		int_line = pci_read_config(self, PCIR_INTLINE, 4);
		pci_set_powerstate(self, PCI_POWERSTATE_D0);
		pci_write_config(self, PCI_CBMEM, reg, 4);
		pci_write_config(self, PCIR_INTLINE, int_line, 4);
	}
	return (0);
}