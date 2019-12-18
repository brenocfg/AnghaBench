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
typedef  int u32 ;
typedef  int u16 ;
struct ata_device {int* id; } ;

/* Variables and functions */
 size_t ATA_ID_EIDE_PIO ; 
 size_t ATA_ID_FIELD_VALID ; 
 int ATA_SHIFT_PIO ; 

__attribute__((used)) static u32 ata_pio_mask_no_iordy(const struct ata_device *adev)
{
	/* If we have no drive specific rule, then PIO 2 is non IORDY */
	if (adev->id[ATA_ID_FIELD_VALID] & 2) {	/* EIDE */
		u16 pio = adev->id[ATA_ID_EIDE_PIO];
		/* Is the speed faster than the drive allows non IORDY ? */
		if (pio) {
			/* This is cycle times not frequency - watch the logic! */
			if (pio > 240)	/* PIO2 is 240nS per cycle */
				return 3 << ATA_SHIFT_PIO;
			return 7 << ATA_SHIFT_PIO;
		}
	}
	return 3 << ATA_SHIFT_PIO;
}