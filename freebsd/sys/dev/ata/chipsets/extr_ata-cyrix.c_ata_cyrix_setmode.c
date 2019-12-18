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
typedef  int uint32_t ;
struct ata_pci_controller {scalar_t__ r_res1; } ;
struct ata_channel {int unit; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 size_t ATA_BMCMD_PORT ; 
 int ATA_MODE_MASK ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int const) ; 
 int ATA_PIO0 ; 
 int ATA_PIO3 ; 
 int ATA_PIO4 ; 
 int ATA_UDMA0 ; 
 int /*<<< orphan*/  ATA_UDMA2 ; 
 int ATA_WDMA0 ; 
 int ATA_WDMA1 ; 
 size_t ata_mode2idx (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_cyrix_setmode(device_t dev, int target, int mode)
{
	struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
	struct ata_channel *ch = device_get_softc(dev);
	int devno = (ch->unit << 1) + target;
	int piomode;
	static const uint32_t piotiming[] = 
	    { 0x00009172, 0x00012171, 0x00020080, 0x00032010, 0x00040010 };
	static const uint32_t dmatiming[] =
	    { 0x00077771, 0x00012121, 0x00002020 };
	static const uint32_t udmatiming[] =
	    { 0x00921250, 0x00911140, 0x00911030 };

	mode = min(mode, ATA_UDMA2);
	/* dont try to set the mode if we dont have the resource */
	if (ctlr->r_res1) {
		if (mode >= ATA_UDMA0) {
			/* Set UDMA timings, and PIO4. */
			ATA_OUTL(ch->r_io[ATA_BMCMD_PORT].res,
			    0x24 + (devno << 3), udmatiming[mode & ATA_MODE_MASK]);
			piomode = ATA_PIO4;
		} else if (mode >= ATA_WDMA0) {
			/* Set WDMA timings, and respective PIO mode. */
			ATA_OUTL(ch->r_io[ATA_BMCMD_PORT].res,
			    0x24 + (devno << 3), dmatiming[mode & ATA_MODE_MASK]);
		        piomode = (mode == ATA_WDMA0) ? ATA_PIO0 :
			    (mode == ATA_WDMA1) ? ATA_PIO3 : ATA_PIO4;
		} else
			piomode = mode;
		/* Set PIO mode calculated above. */
		ATA_OUTL(ch->r_io[ATA_BMCMD_PORT].res,
		    0x20 + (devno << 3), piotiming[ata_mode2idx(piomode)]);
	}
	return (mode);
}