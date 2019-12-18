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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int flags; int features; int lba_low; int lba_mid; int lba_high; int lba_low_exp; int lba_mid_exp; int lba_high_exp; int features_exp; scalar_t__ control; scalar_t__ sector_count_exp; scalar_t__ sector_count; int /*<<< orphan*/  device; int /*<<< orphan*/  command; } ;
struct ccb_ataio {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DEV_LBA ; 
 int CAM_ATAIO_48BIT ; 
 int CAM_ATAIO_FPDMA ; 

void
ata_ncq_cmd(struct ccb_ataio *ataio, uint8_t cmd,
    uint64_t lba, uint16_t sector_count)
{

	ataio->cmd.flags = CAM_ATAIO_48BIT | CAM_ATAIO_FPDMA;
	ataio->cmd.command = cmd;
	ataio->cmd.features = sector_count;
	ataio->cmd.lba_low = lba;
	ataio->cmd.lba_mid = lba >> 8;
	ataio->cmd.lba_high = lba >> 16;
	ataio->cmd.device = ATA_DEV_LBA;
	ataio->cmd.lba_low_exp = lba >> 24;
	ataio->cmd.lba_mid_exp = lba >> 32;
	ataio->cmd.lba_high_exp = lba >> 40;
	ataio->cmd.features_exp = sector_count >> 8;
	ataio->cmd.sector_count = 0;
	ataio->cmd.sector_count_exp = 0;
	ataio->cmd.control = 0;
}