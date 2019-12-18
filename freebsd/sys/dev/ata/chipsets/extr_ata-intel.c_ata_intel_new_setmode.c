#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {int unit; int flags; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 int ATA_MODE_MASK ; 
 int ATA_PIO4 ; 
 int ATA_SATA ; 
 int ATA_UDMA0 ; 
 int ATA_UDMA2 ; 
 int ATA_UDMA3 ; 
 int ATA_UDMA5 ; 
 scalar_t__ ata_dma_check_80pin ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  ata_print_cable (int /*<<< orphan*/ ,char*) ; 
 int ata_sata_setmode (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_intel_new_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
	struct ata_pci_controller *ctlr = device_get_softc(parent);
	struct ata_channel *ch = device_get_softc(dev);
	int devno = (ch->unit << 1) + target;
	int piomode;
	u_int32_t reg40 = pci_read_config(parent, 0x40, 4);
	u_int8_t reg44 = pci_read_config(parent, 0x44, 1);
	u_int8_t reg48 = pci_read_config(parent, 0x48, 1);
	u_int16_t reg4a = pci_read_config(parent, 0x4a, 2);
	u_int16_t reg54 = pci_read_config(parent, 0x54, 2);
	u_int32_t mask40 = 0, new40 = 0;
	u_int8_t mask44 = 0, new44 = 0;
	static const uint8_t timings[] =
	    { 0x00, 0x00, 0x10, 0x21, 0x23, 0x00, 0x21, 0x23 };
	static const uint8_t utimings[] =
	    { 0x00, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02 };

	/* In combined mode, skip PATA stuff for SATA channel. */
	if (ch->flags & ATA_SATA)
		return (ata_sata_setmode(dev, target, mode));

	mode = min(mode, ctlr->chip->max_dma);
	if (ata_dma_check_80pin && mode > ATA_UDMA2 &&
	    !(reg54 & (0x10 << devno))) {
		ata_print_cable(dev, "controller");
		mode = ATA_UDMA2;
	}
	/* Enable/disable UDMA and set timings. */
	if (mode >= ATA_UDMA0) {
	    pci_write_config(parent, 0x48, reg48 | (0x0001 << devno), 2);
	    pci_write_config(parent, 0x4a,
		(reg4a & ~(0x3 << (devno << 2))) |
		(utimings[mode & ATA_MODE_MASK] << (devno<<2)), 2);
	    piomode = ATA_PIO4;
	} else {
	    pci_write_config(parent, 0x48, reg48 & ~(0x0001 << devno), 2);
	    pci_write_config(parent, 0x4a, (reg4a & ~(0x3 << (devno << 2))),2);
	    piomode = mode;
	}
	reg54 |= 0x0400;
	/* Set UDMA reference clock (33/66/133MHz). */
	reg54 &= ~(0x1001 << devno);
	if (mode >= ATA_UDMA5)
	    reg54 |= (0x1000 << devno);
	else if (mode >= ATA_UDMA3)
	    reg54 |= (0x1 << devno);
	pci_write_config(parent, 0x54, reg54, 2);
	/* Allow PIO/WDMA timing controls. */
	reg40 &= ~0x00ff00ff;
	reg40 |= 0x40774077;
	/* Set PIO/WDMA timings. */
	if (target == 0) {
	    mask40 = 0x3300;
	    new40 = timings[ata_mode2idx(piomode)] << 8;
	} else {
	    mask44 = 0x0f;
	    new44 = ((timings[ata_mode2idx(piomode)] & 0x30) >> 2) |
		    (timings[ata_mode2idx(piomode)] & 0x03);
	}
	if (ch->unit) {
	    mask40 <<= 16;
	    new40 <<= 16;
	    mask44 <<= 4;
	    new44 <<= 4;
	}
	pci_write_config(parent, 0x40, (reg40 & ~mask40) | new40, 4);
	pci_write_config(parent, 0x44, (reg44 & ~mask44) | new44, 1);
	return (mode);
}