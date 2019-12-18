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
typedef  int u_int16_t ;
struct ata_pci_controller {TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 int ATA_MODE_MASK ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 int ATA_UDMA2 ; 
 int ATA_UDMA3 ; 
 int ATA_UDMA5 ; 
 scalar_t__ ata_atapi (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ata_dma_check_80pin ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  ata_print_cable (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_ite_8213_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
	struct ata_pci_controller *ctlr = device_get_softc(parent);
	int piomode;
	u_int16_t reg40 = pci_read_config(parent, 0x40, 2);
	u_int8_t reg44 = pci_read_config(parent, 0x44, 1);
	u_int8_t reg48 = pci_read_config(parent, 0x48, 1);
	u_int16_t reg4a = pci_read_config(parent, 0x4a, 2);
	u_int16_t reg54 = pci_read_config(parent, 0x54, 2);
	u_int16_t mask40 = 0, new40 = 0;
	u_int8_t mask44 = 0, new44 = 0;
	static const uint8_t timings[] =
	    { 0x00, 0x00, 0x10, 0x21, 0x23, 0x00, 0x21, 0x23 };
	static const uint8_t utimings[] =
	    { 0x00, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02 };

	mode = min(mode, ctlr->chip->max_dma);

	if (ata_dma_check_80pin && mode > ATA_UDMA2 &&
	    !(reg54 & (0x10 << target))) {
		ata_print_cable(dev, "controller");
		mode = ATA_UDMA2;
	}
	/* Enable/disable UDMA and set timings. */
	if (mode >= ATA_UDMA0) {
	    pci_write_config(parent, 0x48, reg48 | (0x0001 << target), 2);
	    pci_write_config(parent, 0x4a,
			     (reg4a & ~(0x3 << (target << 2))) |
			     (utimings[mode & ATA_MODE_MASK] << (target<<2)), 2);
	    piomode = ATA_PIO4;
	} else {
	    pci_write_config(parent, 0x48, reg48 & ~(0x0001 << target), 2);
	    pci_write_config(parent, 0x4a, (reg4a & ~(0x3 << (target << 2))),2);
	    piomode = mode;
	}
	/* Set UDMA reference clock (33/66/133MHz). */
	reg54 &= ~(0x1001 << target);
	if (mode >= ATA_UDMA5)
	    reg54 |= (0x1000 << target);
	else if (mode >= ATA_UDMA3)
	    reg54 |= (0x1 << target);
	pci_write_config(parent, 0x54, reg54, 2);
	/* Allow PIO/WDMA timing controls. */
	reg40 &= 0xff00;
	reg40 |= 0x4033;
	/* Set PIO/WDMA timings. */
	if (target == 0) {
	    reg40 |= (ata_atapi(dev, target) ? 0x04 : 0x00);
	    mask40 = 0x3300;
	    new40 = timings[ata_mode2idx(piomode)] << 8;
	}
	else {
	    reg40 |= (ata_atapi(dev, target) ? 0x40 : 0x00);
	    mask44 = 0x0f;
	    new44 = ((timings[ata_mode2idx(piomode)] & 0x30) >> 2) |
		    (timings[ata_mode2idx(piomode)] & 0x03);
	}
	pci_write_config(parent, 0x40, (reg40 & ~mask40) | new40, 4);
	pci_write_config(parent, 0x44, (reg44 & ~mask44) | new44, 1);
	return (mode);
}