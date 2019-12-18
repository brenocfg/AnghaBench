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
struct ata_cmd {int /*<<< orphan*/  command; int /*<<< orphan*/  lba_high; int /*<<< orphan*/  lba_high_exp; int /*<<< orphan*/  lba_mid; int /*<<< orphan*/  lba_mid_exp; int /*<<< orphan*/  lba_low; int /*<<< orphan*/  lba_low_exp; int /*<<< orphan*/  sector_count; int /*<<< orphan*/  sector_count_exp; int /*<<< orphan*/  features; int /*<<< orphan*/  features_exp; int /*<<< orphan*/  control; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct ata_cmd cmd; } ;
union ccb {TYPE_1__ ataio; } ;
struct mvs_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_COMMAND ; 
 int /*<<< orphan*/  ATA_CONTROL ; 
 int /*<<< orphan*/  ATA_COUNT ; 
 int /*<<< orphan*/  ATA_CYL_LSB ; 
 int /*<<< orphan*/  ATA_CYL_MSB ; 
 int /*<<< orphan*/  ATA_DRIVE ; 
 int /*<<< orphan*/  ATA_FEATURE ; 
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_SECTOR ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_tfd_write(device_t dev, union ccb *ccb)
{
	struct mvs_channel *ch = device_get_softc(dev);
	struct ata_cmd *cmd = &ccb->ataio.cmd;

	ATA_OUTB(ch->r_mem, ATA_DRIVE, cmd->device);
	ATA_OUTB(ch->r_mem, ATA_CONTROL, cmd->control);
	ATA_OUTB(ch->r_mem, ATA_FEATURE, cmd->features_exp);
	ATA_OUTB(ch->r_mem, ATA_FEATURE, cmd->features);
	ATA_OUTB(ch->r_mem, ATA_COUNT, cmd->sector_count_exp);
	ATA_OUTB(ch->r_mem, ATA_COUNT, cmd->sector_count);
	ATA_OUTB(ch->r_mem, ATA_SECTOR, cmd->lba_low_exp);
	ATA_OUTB(ch->r_mem, ATA_SECTOR, cmd->lba_low);
	ATA_OUTB(ch->r_mem, ATA_CYL_LSB, cmd->lba_mid_exp);
	ATA_OUTB(ch->r_mem, ATA_CYL_LSB, cmd->lba_mid);
	ATA_OUTB(ch->r_mem, ATA_CYL_MSB, cmd->lba_high_exp);
	ATA_OUTB(ch->r_mem, ATA_CYL_MSB, cmd->lba_high);
	ATA_OUTB(ch->r_mem, ATA_COMMAND, cmd->command);
}