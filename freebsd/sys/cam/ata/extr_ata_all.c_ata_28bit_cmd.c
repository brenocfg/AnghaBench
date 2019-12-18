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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int lba_low; int lba_mid; int lba_high; int device; scalar_t__ sector_count; scalar_t__ features; scalar_t__ command; int /*<<< orphan*/  flags; } ;
struct ccb_ataio {TYPE_1__ cmd; } ;

/* Variables and functions */
 int ATA_DEV_LBA ; 
 scalar_t__ ATA_DOWNLOAD_MICROCODE_DMA ; 
 scalar_t__ ATA_READ_BUFFER_DMA ; 
 scalar_t__ ATA_READ_DMA ; 
 scalar_t__ ATA_READ_DMA_QUEUED ; 
 scalar_t__ ATA_TRUSTED_RECEIVE_DMA ; 
 scalar_t__ ATA_TRUSTED_SEND_DMA ; 
 scalar_t__ ATA_WRITE_BUFFER_DMA ; 
 scalar_t__ ATA_WRITE_DMA ; 
 scalar_t__ ATA_WRITE_DMA_QUEUED ; 
 int /*<<< orphan*/  CAM_ATAIO_DMA ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 

void
ata_28bit_cmd(struct ccb_ataio *ataio, uint8_t cmd, uint8_t features,
    uint32_t lba, uint8_t sector_count)
{
	bzero(&ataio->cmd, sizeof(ataio->cmd));
	ataio->cmd.flags = 0;
	if (cmd == ATA_READ_DMA ||
	    cmd == ATA_READ_DMA_QUEUED ||
	    cmd == ATA_WRITE_DMA ||
	    cmd == ATA_WRITE_DMA_QUEUED ||
	    cmd == ATA_TRUSTED_RECEIVE_DMA ||
	    cmd == ATA_TRUSTED_SEND_DMA ||
	    cmd == ATA_DOWNLOAD_MICROCODE_DMA ||
	    cmd == ATA_READ_BUFFER_DMA ||
	    cmd == ATA_WRITE_BUFFER_DMA)
		ataio->cmd.flags |= CAM_ATAIO_DMA;
	ataio->cmd.command = cmd;
	ataio->cmd.features = features;
	ataio->cmd.lba_low = lba;
	ataio->cmd.lba_mid = lba >> 8;
	ataio->cmd.lba_high = lba >> 16;
	ataio->cmd.device = ATA_DEV_LBA | ((lba >> 24) & 0x0f);
	ataio->cmd.sector_count = sector_count;
}