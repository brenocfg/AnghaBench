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
struct TYPE_2__ {size_t cfg1; int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 int ATA_MODE_MASK ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int const,int) ; 

__attribute__((used)) static int
ata_via_old_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
	struct ata_pci_controller *ctlr = device_get_softc(parent);
	struct ata_channel *ch = device_get_softc(dev);
	int devno = (ch->unit << 1) + target;
	int reg = 0x53 - devno;
	int piomode;
	static const uint8_t timings[] =
	    { 0xa8, 0x65, 0x42, 0x22, 0x20, 0xa8, 0x22, 0x20 };
	static const uint8_t modes[][7] = {
	    { 0xc2, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x00 },   /* VIA ATA33 */
	    { 0xee, 0xec, 0xea, 0xe9, 0xe8, 0x00, 0x00 },   /* VIA ATA66 */
	    { 0xf7, 0xf6, 0xf4, 0xf2, 0xf1, 0xf0, 0x00 },   /* VIA ATA100 */
	    { 0xf7, 0xf7, 0xf6, 0xf4, 0xf2, 0xf1, 0xf0 } }; /* VIA ATA133 */

	mode = min(mode, ctlr->chip->max_dma);
	/* Set UDMA timings */
	if (mode >= ATA_UDMA0) {
	    pci_write_config(parent, reg,
			     modes[ctlr->chip->cfg1][mode & ATA_MODE_MASK], 1);
	    piomode = ATA_PIO4;
	} else {
	    pci_write_config(parent, reg, 0x8b, 1);
	    piomode = mode;
	}
	/* Set WDMA/PIO timings */
	pci_write_config(parent, reg - 0x08,timings[ata_mode2idx(piomode)], 1);
	return (mode);
}