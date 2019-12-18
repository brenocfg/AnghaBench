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

/* Variables and functions */
 int ATA_DMA_MASK ; 
 int ATA_MODE_MASK ; 
 int ATA_PIO0 ; 
 int ATA_UDMA0 ; 
 int ATA_WDMA0 ; 

int
ata_mode2idx(int mode)
{
    if ((mode & ATA_DMA_MASK) == ATA_UDMA0)
	return (mode & ATA_MODE_MASK) + 8;
    if ((mode & ATA_DMA_MASK) == ATA_WDMA0)
	return (mode & ATA_MODE_MASK) + 5;
    return (mode & ATA_MODE_MASK) - ATA_PIO0;
}