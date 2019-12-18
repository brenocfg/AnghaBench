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
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIP_STORAGE_IDE_MODEPRIM ; 
 int PCIP_STORAGE_IDE_MODESEC ; 
 int PCIR_BAR (int) ; 
 int PCIR_PROGIF ; 
 int SYS_RES_IOPORT ; 
 int /*<<< orphan*/  pci_add_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource_list*,int,int) ; 
 scalar_t__ pci_mapbase (int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,int,int,int) ; 
 int /*<<< orphan*/  resource_list_reserve (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_ata_maps(device_t bus, device_t dev, struct resource_list *rl, int force,
    uint32_t prefetchmask)
{
	int rid, type, progif;
#if 0
	/* if this device supports PCI native addressing use it */
	progif = pci_read_config(dev, PCIR_PROGIF, 1);
	if ((progif & 0x8a) == 0x8a) {
		if (pci_mapbase(pci_read_config(dev, PCIR_BAR(0), 4)) &&
		    pci_mapbase(pci_read_config(dev, PCIR_BAR(2), 4))) {
			printf("Trying ATA native PCI addressing mode\n");
			pci_write_config(dev, PCIR_PROGIF, progif | 0x05, 1);
		}
	}
#endif
	progif = pci_read_config(dev, PCIR_PROGIF, 1);
	type = SYS_RES_IOPORT;
	if (progif & PCIP_STORAGE_IDE_MODEPRIM) {
		pci_add_map(bus, dev, PCIR_BAR(0), rl, force,
		    prefetchmask & (1 << 0));
		pci_add_map(bus, dev, PCIR_BAR(1), rl, force,
		    prefetchmask & (1 << 1));
	} else {
		rid = PCIR_BAR(0);
		resource_list_add(rl, type, rid, 0x1f0, 0x1f7, 8);
		(void)resource_list_reserve(rl, bus, dev, type, &rid, 0x1f0,
		    0x1f7, 8, 0);
		rid = PCIR_BAR(1);
		resource_list_add(rl, type, rid, 0x3f6, 0x3f6, 1);
		(void)resource_list_reserve(rl, bus, dev, type, &rid, 0x3f6,
		    0x3f6, 1, 0);
	}
	if (progif & PCIP_STORAGE_IDE_MODESEC) {
		pci_add_map(bus, dev, PCIR_BAR(2), rl, force,
		    prefetchmask & (1 << 2));
		pci_add_map(bus, dev, PCIR_BAR(3), rl, force,
		    prefetchmask & (1 << 3));
	} else {
		rid = PCIR_BAR(2);
		resource_list_add(rl, type, rid, 0x170, 0x177, 8);
		(void)resource_list_reserve(rl, bus, dev, type, &rid, 0x170,
		    0x177, 8, 0);
		rid = PCIR_BAR(3);
		resource_list_add(rl, type, rid, 0x376, 0x376, 1);
		(void)resource_list_reserve(rl, bus, dev, type, &rid, 0x376,
		    0x376, 1, 0);
	}
	pci_add_map(bus, dev, PCIR_BAR(4), rl, force,
	    prefetchmask & (1 << 4));
	pci_add_map(bus, dev, PCIR_BAR(5), rl, force,
	    prefetchmask & (1 << 5));
}