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
struct ata_params {int dummy; } ;

/* Variables and functions */
 int ATA_DMA_MAX ; 
 int ATA_UDMA0 ; 
 int ATA_WDMA0 ; 
 scalar_t__ ata_max_pmode (struct ata_params*) ; 
 scalar_t__ ata_max_umode (struct ata_params*) ; 
 scalar_t__ ata_max_wmode (struct ata_params*) ; 
 int min (int,scalar_t__) ; 

int
ata_max_mode(struct ata_params *ap, int maxmode)
{

	if (maxmode == 0)
		maxmode = ATA_DMA_MAX;
	if (maxmode >= ATA_UDMA0 && ata_max_umode(ap) > 0)
		return (min(maxmode, ata_max_umode(ap)));
	if (maxmode >= ATA_WDMA0 && ata_max_wmode(ap) > 0)
		return (min(maxmode, ata_max_wmode(ap)));
	return (min(maxmode, ata_max_pmode(ap)));
}