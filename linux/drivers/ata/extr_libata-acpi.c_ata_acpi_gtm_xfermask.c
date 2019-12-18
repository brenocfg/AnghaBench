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
typedef  int /*<<< orphan*/  u8 ;
struct ata_device {int devno; } ;
struct ata_acpi_gtm {int flags; TYPE_1__* drive; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  pio; } ;

/* Variables and functions */
 unsigned int ATA_SHIFT_MWDMA ; 
 unsigned int ATA_SHIFT_PIO ; 
 unsigned int ATA_SHIFT_UDMA ; 
 int /*<<< orphan*/  ata_timing_cycle2mode (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long ata_xfer_mode2mask (int /*<<< orphan*/ ) ; 

unsigned long ata_acpi_gtm_xfermask(struct ata_device *dev,
				    const struct ata_acpi_gtm *gtm)
{
	unsigned long xfer_mask = 0;
	unsigned int type;
	int unit;
	u8 mode;

	/* we always use the 0 slot for crap hardware */
	unit = dev->devno;
	if (!(gtm->flags & 0x10))
		unit = 0;

	/* PIO */
	mode = ata_timing_cycle2mode(ATA_SHIFT_PIO, gtm->drive[unit].pio);
	xfer_mask |= ata_xfer_mode2mask(mode);

	/* See if we have MWDMA or UDMA data. We don't bother with
	 * MWDMA if UDMA is available as this means the BIOS set UDMA
	 * and our error changedown if it works is UDMA to PIO anyway.
	 */
	if (!(gtm->flags & (1 << (2 * unit))))
		type = ATA_SHIFT_MWDMA;
	else
		type = ATA_SHIFT_UDMA;

	mode = ata_timing_cycle2mode(type, gtm->drive[unit].dma);
	xfer_mask |= ata_xfer_mode2mask(mode);

	return xfer_mask;
}