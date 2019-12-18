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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_BCR_VGA_ENABLE ; 
 scalar_t__ PCIC_DISPLAY ; 
 scalar_t__ PCIC_OLD ; 
 int PCIM_CMD_INTxDIS ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_BRIDGECTL_1 ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 scalar_t__ PCIS_OLD_VGA ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_flags (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int vga_pci_default_unit ; 

int
vga_pci_is_boot_display(device_t dev)
{
	int unit;
	device_t pcib;
	uint16_t config;

	/* Check that the given device is a video card */
	if ((pci_get_class(dev) != PCIC_DISPLAY &&
	    (pci_get_class(dev) != PCIC_OLD ||
	     pci_get_subclass(dev) != PCIS_OLD_VGA)))
		return (0);

	unit = device_get_unit(dev);

	if (vga_pci_default_unit >= 0) {
		/*
		 * The boot display device was determined by a previous
		 * call to this function, or the user forced it using
		 * the hw.pci.default_vgapci_unit tunable.
		 */
		return (vga_pci_default_unit == unit);
	}

	/*
	 * The primary video card used as a boot display must have the
	 * "I/O" and "Memory Address Space Decoding" bits set in its
	 * Command register.
	 *
	 * Furthermore, if the card is attached to a bridge, instead of
	 * the root PCI bus, the bridge must have the "VGA Enable" bit
	 * set in its Control register.
	 */

	pcib = device_get_parent(device_get_parent(dev));
	if (device_get_devclass(device_get_parent(pcib)) ==
	    devclass_find("pci")) {
		/*
		 * The parent bridge is a PCI-to-PCI bridge: check the
		 * value of the "VGA Enable" bit.
		 */
		config = pci_read_config(pcib, PCIR_BRIDGECTL_1, 2);
		if ((config & PCIB_BCR_VGA_ENABLE) == 0)
			return (0);
	}

	config = pci_read_config(dev, PCIR_COMMAND, 2);
	if ((config & (PCIM_CMD_PORTEN | PCIM_CMD_MEMEN)) == 0)
		return (0);

	/*
	 * Disable interrupts until a chipset driver is loaded for
	 * this PCI device. Else unhandled display adapter interrupts
	 * might freeze the CPU.
	 */
	pci_write_config(dev, PCIR_COMMAND, config | PCIM_CMD_INTxDIS, 2);

	/* This video card is the boot display: record its unit number. */
	vga_pci_default_unit = unit;
	device_set_flags(dev, 1);

	return (1);
}