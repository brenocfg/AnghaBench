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
struct ata_device {scalar_t__ class; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 int ATA_SHIFT_UDMA ; 
 int /*<<< orphan*/  bad_ata100_5 ; 
 scalar_t__ hpt_dma_blacklisted (struct ata_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long hpt370a_filter(struct ata_device *adev, unsigned long mask)
{
	if (adev->class == ATA_DEV_ATA) {
		if (hpt_dma_blacklisted(adev, "UDMA100", bad_ata100_5))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	}
	return mask;
}