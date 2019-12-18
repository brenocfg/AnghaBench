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
struct TYPE_2__ {scalar_t__ cfg1; int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 int ATA_MODE_MASK ; 
 int ATA_PIO0 ; 
 int ATA_PIO3 ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 int ATA_WDMA0 ; 
 int ATA_WDMA1 ; 
 scalar_t__ SWKS_33 ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ata_serverworks_setmode(device_t dev, int target, int mode)
{
	device_t parent = device_get_parent(dev);
        struct ata_pci_controller *ctlr = device_get_softc(parent);
	struct ata_channel *ch = device_get_softc(dev);
        int devno = (ch->unit << 1) + target;
        int offset = (devno ^ 0x01) << 3;
	int piomode;
	static const uint8_t piotimings[] = { 0x5d, 0x47, 0x34, 0x22, 0x20 };
	static const uint8_t dmatimings[] = { 0x77, 0x21, 0x20 };

	mode = min(mode, ctlr->chip->max_dma);
	if (mode >= ATA_UDMA0) {
	    /* Set UDMA mode, enable UDMA, set WDMA2/PIO4 */
	    pci_write_config(parent, 0x56, 
			     (pci_read_config(parent, 0x56, 2) &
			      ~(0xf << (devno << 2))) |
			     ((mode & ATA_MODE_MASK) << (devno << 2)), 2);
	    pci_write_config(parent, 0x54,
			     pci_read_config(parent, 0x54, 1) |
			     (0x01 << devno), 1);
	    pci_write_config(parent, 0x44, 
			     (pci_read_config(parent, 0x44, 4) &
			      ~(0xff << offset)) |
			     (dmatimings[2] << offset), 4);
	    piomode = ATA_PIO4;
	} else if (mode >= ATA_WDMA0) {
	    /* Disable UDMA, set WDMA mode and timings, calculate PIO. */
	    pci_write_config(parent, 0x54,
			     pci_read_config(parent, 0x54, 1) &
			      ~(0x01 << devno), 1);
	    pci_write_config(parent, 0x44, 
			     (pci_read_config(parent, 0x44, 4) &
			      ~(0xff << offset)) |
			     (dmatimings[mode & ATA_MODE_MASK] << offset), 4);
	    piomode = (mode == ATA_WDMA0) ? ATA_PIO0 :
		(mode == ATA_WDMA1) ? ATA_PIO3 : ATA_PIO4;
	} else {
	    /* Disable UDMA, set requested PIO. */
	    pci_write_config(parent, 0x54,
			     pci_read_config(parent, 0x54, 1) &
			     ~(0x01 << devno), 1);
	    piomode = mode;
	}
	/* Set PIO mode and timings, calculated above. */
	if (ctlr->chip->cfg1 != SWKS_33) {
		pci_write_config(parent, 0x4a,
			 (pci_read_config(parent, 0x4a, 2) &
			  ~(0xf << (devno << 2))) |
			 ((piomode - ATA_PIO0) << (devno<<2)),2);
	}
	pci_write_config(parent, 0x40, 
			 (pci_read_config(parent, 0x40, 4) &
			  ~(0xff << offset)) |
			 (piotimings[ata_mode2idx(piomode)] << offset), 4);
	return (mode);
}