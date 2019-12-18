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

/* Variables and functions */
#define  CFGMECH_1 130 
#define  CFGMECH_2 129 
#define  CFGMECH_PCIE 128 
 int /*<<< orphan*/  CONF1_ADDR_PORT ; 
 int /*<<< orphan*/  CONF1_DATA_PORT ; 
 int /*<<< orphan*/  CONF2_ENABLE_PORT ; 
 int /*<<< orphan*/  CONF2_FORWARD_PORT ; 
 unsigned int PCI_BUSMAX ; 
 unsigned int PCI_FUNCMAX ; 
 unsigned int PCI_REGMAX ; 
 int cfgmech ; 
 unsigned int devmax ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
pci_cfgenable(unsigned bus, unsigned slot, unsigned func, int reg, int bytes)
{
	int dataport = 0;

	if (bus <= PCI_BUSMAX
	    && slot < devmax
	    && func <= PCI_FUNCMAX
	    && (unsigned)reg <= PCI_REGMAX
	    && bytes != 3
	    && (unsigned)bytes <= 4
	    && (reg & (bytes - 1)) == 0) {
		switch (cfgmech) {
		case CFGMECH_PCIE:
		case CFGMECH_1:
			outl(CONF1_ADDR_PORT, (1U << 31)
			    | (bus << 16) | (slot << 11) 
			    | (func << 8) | (reg & ~0x03));
			dataport = CONF1_DATA_PORT + (reg & 0x03);
			break;
		case CFGMECH_2:
			outb(CONF2_ENABLE_PORT, 0xf0 | (func << 1));
			outb(CONF2_FORWARD_PORT, bus);
			dataport = 0xc000 | (slot << 8) | reg;
			break;
		}
	}
	return (dataport);
}