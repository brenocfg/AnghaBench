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
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg2; } ;

/* Variables and functions */
 int ATA_MODE_MASK ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 int ATA_WDMA0 ; 
 int VIABAR ; 
 size_t ata_mode2idx (int) ; 
 int ata_sata_setmode (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int const,int) ; 

__attribute__((used)) static int
ata_via_new_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
	struct ata_pci_controller *ctlr = device_get_softc(parent);
	struct ata_channel *ch = device_get_softc(dev);

	if ((ctlr->chip->cfg2 & VIABAR) && (ch->unit > 1)) {
	    int piomode;
    	    static const uint8_t pio_timings[] =
		{ 0xa8, 0x65, 0x65, 0x32, 0x20 };
	    static const uint8_t dma_timings[] =
		{ 0xee, 0xe8, 0xe6, 0xe4, 0xe2, 0xe1, 0xe0 };

	    /* This chip can't do WDMA. */
	    if (mode >= ATA_WDMA0 && mode < ATA_UDMA0)
		mode = ATA_PIO4;
	    if (mode >= ATA_UDMA0) {
		pci_write_config(parent, 0xb3,
				 dma_timings[mode & ATA_MODE_MASK], 1);
		piomode = ATA_PIO4;
	    } else
		piomode = mode;
	    pci_write_config(parent, 0xab, pio_timings[ata_mode2idx(piomode)], 1);
	} else
		mode = ata_sata_setmode(dev, target, mode);
	return (mode);
}