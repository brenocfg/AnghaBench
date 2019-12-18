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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIEM_FLAGS_TYPE ; 
 int /*<<< orphan*/  PCIEM_TYPE_DOWNSTREAM_PORT ; 
 int /*<<< orphan*/  PCIEM_TYPE_ROOT_PORT ; 
 scalar_t__ PCIER_FLAGS ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int PCI_SLOTMAX ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

int
pcib_maxslots(device_t dev)
{
#if !defined(__amd64__) && !defined(__i386__)
	uint32_t pcie_pos;
	uint16_t val;

	/*
	 * If this is a PCIe rootport or downstream switch port, there's only
	 * one slot permitted.
	 */
	if (pci_find_cap(dev, PCIY_EXPRESS, &pcie_pos) == 0) {
		val = pci_read_config(dev, pcie_pos + PCIER_FLAGS, 2);
		val &= PCIEM_FLAGS_TYPE;
		if (val == PCIEM_TYPE_ROOT_PORT ||
		    val == PCIEM_TYPE_DOWNSTREAM_PORT)
			return (0);
	}
#endif
	return (PCI_SLOTMAX);
}