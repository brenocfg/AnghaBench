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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int features; int lba_low; int lba_mid; int lba_high; int lba_low_exp; int lba_mid_exp; int lba_high_exp; int features_exp; int sector_count; int sector_count_exp; scalar_t__ control; int /*<<< orphan*/  device; scalar_t__ command; int /*<<< orphan*/  flags; } ;
struct ccb_ataio {TYPE_1__ cmd; } ;

/* Variables and functions */
 scalar_t__ ATA_DATA_SET_MANAGEMENT ; 
 int /*<<< orphan*/  ATA_DEV_LBA ; 
 scalar_t__ ATA_READ_DMA48 ; 
 scalar_t__ ATA_READ_DMA_QUEUED48 ; 
 scalar_t__ ATA_READ_LOG_DMA_EXT ; 
 scalar_t__ ATA_READ_STREAM_DMA48 ; 
 scalar_t__ ATA_WRITE_DMA48 ; 
 scalar_t__ ATA_WRITE_DMA_FUA48 ; 
 scalar_t__ ATA_WRITE_DMA_QUEUED48 ; 
 scalar_t__ ATA_WRITE_DMA_QUEUED_FUA48 ; 
 scalar_t__ ATA_WRITE_LOG_DMA_EXT ; 
 scalar_t__ ATA_WRITE_STREAM_DMA48 ; 
 int /*<<< orphan*/  CAM_ATAIO_48BIT ; 
 int /*<<< orphan*/  CAM_ATAIO_DMA ; 

void
ata_48bit_cmd(struct ccb_ataio *ataio, uint8_t cmd, uint16_t features,
    uint64_t lba, uint16_t sector_count)
{

	ataio->cmd.flags = CAM_ATAIO_48BIT;
	if (cmd == ATA_READ_DMA48 ||
	    cmd == ATA_READ_DMA_QUEUED48 ||
	    cmd == ATA_READ_STREAM_DMA48 ||
	    cmd == ATA_WRITE_DMA48 ||
	    cmd == ATA_WRITE_DMA_FUA48 ||
	    cmd == ATA_WRITE_DMA_QUEUED48 ||
	    cmd == ATA_WRITE_DMA_QUEUED_FUA48 ||
	    cmd == ATA_WRITE_STREAM_DMA48 ||
	    cmd == ATA_DATA_SET_MANAGEMENT ||
	    cmd == ATA_READ_LOG_DMA_EXT ||
	    cmd == ATA_WRITE_LOG_DMA_EXT)
		ataio->cmd.flags |= CAM_ATAIO_DMA;
	ataio->cmd.command = cmd;
	ataio->cmd.features = features;
	ataio->cmd.lba_low = lba;
	ataio->cmd.lba_mid = lba >> 8;
	ataio->cmd.lba_high = lba >> 16;
	ataio->cmd.device = ATA_DEV_LBA;
	ataio->cmd.lba_low_exp = lba >> 24;
	ataio->cmd.lba_mid_exp = lba >> 32;
	ataio->cmd.lba_high_exp = lba >> 40;
	ataio->cmd.features_exp = features >> 8;
	ataio->cmd.sector_count = sector_count;
	ataio->cmd.sector_count_exp = sector_count >> 8;
	ataio->cmd.control = 0;
}