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
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_MODE_MASK ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 int /*<<< orphan*/  ATA_UDMA2 ; 
 int ATA_WDMA0 ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int const,int) ; 

__attribute__((used)) static int
ata_national_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
	struct ata_channel *ch = device_get_softc(dev);
	int devno = (ch->unit << 1) + target;
	int piomode;
	static const uint32_t piotiming[] =
	    { 0x9172d132, 0x21717121, 0x00803020, 0x20102010, 0x00100010,
	      0x9172d132, 0x20102010, 0x00100010 };
	static const uint32_t dmatiming[] =
	    { 0x80077771, 0x80012121, 0x80002020 };
	static const uint32_t udmatiming[] =
	    { 0x80921250, 0x80911140, 0x80911030 };

	mode = min(mode, ATA_UDMA2);

	if (mode >= ATA_UDMA0) {
	    pci_write_config(parent, 0x44 + (devno << 3),
			     udmatiming[mode & ATA_MODE_MASK], 4);
	    piomode = ATA_PIO4;
	} else if (mode >= ATA_WDMA0) {
	    pci_write_config(parent, 0x44 + (devno << 3),
			     dmatiming[mode & ATA_MODE_MASK], 4);
	    piomode = mode;
	} else {
	    pci_write_config(parent, 0x44 + (devno << 3),
			     pci_read_config(parent, 0x44 + (devno << 3), 4) |
			     0x80000000, 4);
	    piomode = mode;
	}
	pci_write_config(parent, 0x40 + (devno << 3),
			 piotiming[ata_mode2idx(piomode)], 4);
	return (mode);
}