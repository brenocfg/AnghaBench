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
typedef  int uint16_t ;
typedef  int u_int8_t ;
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg2; int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 int ATA_MODE_MASK ; 
 int ATA_PIO0 ; 
 int ATA_PIO3 ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 int ATA_UDMA2 ; 
 int ATA_WDMA0 ; 
 int ATA_WDMA1 ; 
 int SII_SETCLK ; 
 scalar_t__ ata_dma_check_80pin ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  ata_print_cable (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int const,int) ; 

__attribute__((used)) static int
ata_sii_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
	struct ata_pci_controller *ctlr = device_get_softc(parent);
	struct ata_channel *ch = device_get_softc(dev);
	int rego = (ch->unit << 4) + (target << 1);
	int mreg = ch->unit ? 0x84 : 0x80;
	int mask = 0x03 << (target << 2);
	int mval = pci_read_config(parent, mreg, 1) & ~mask;
	int piomode;
	u_int8_t preg = 0xa4 + rego;
	u_int8_t dreg = 0xa8 + rego;
	u_int8_t ureg = 0xac + rego;
	static const uint16_t piotimings[] =
	    { 0x328a, 0x2283, 0x1104, 0x10c3, 0x10c1 };
	static const uint16_t dmatimings[] = { 0x2208, 0x10c2, 0x10c1 };
	static const uint8_t udmatimings[] =
	    { 0xf, 0xb, 0x7, 0x5, 0x3, 0x2, 0x1 };

	mode = min(mode, ctlr->chip->max_dma);

	if (ctlr->chip->cfg2 & SII_SETCLK) {
	    if (ata_dma_check_80pin && mode > ATA_UDMA2 &&
		(pci_read_config(parent, 0x79, 1) &
				 (ch->unit ? 0x02 : 0x01))) {
		ata_print_cable(dev, "controller");
		mode = ATA_UDMA2;
	    }
	}
	if (mode >= ATA_UDMA0) {
		pci_write_config(parent, mreg,
			 mval | (0x03 << (target << 2)), 1);
		pci_write_config(parent, ureg, 
			 (pci_read_config(parent, ureg, 1) & ~0x3f) |
			 udmatimings[mode & ATA_MODE_MASK], 1);
		piomode = ATA_PIO4;
	} else if (mode >= ATA_WDMA0) {
		pci_write_config(parent, mreg,
			 mval | (0x02 << (target << 2)), 1);
		pci_write_config(parent, dreg, dmatimings[mode & ATA_MODE_MASK], 2);
		piomode = (mode == ATA_WDMA0) ? ATA_PIO0 :
		    (mode == ATA_WDMA1) ? ATA_PIO3 : ATA_PIO4;
	} else {
		pci_write_config(parent, mreg,
			 mval | (0x01 << (target << 2)), 1);
		piomode = mode;
	}
	pci_write_config(parent, preg, piotimings[ata_mode2idx(piomode)], 2);
	return (mode);
}