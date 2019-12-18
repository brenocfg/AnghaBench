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
struct TYPE_2__ {int features; int sector_count; int lba_low; int lba_mid; int lba_high; int device; int /*<<< orphan*/  command; scalar_t__ flags; } ;
struct ccb_ataio {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_WRITE_PM ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 

void
ata_pm_write_cmd(struct ccb_ataio *ataio, int reg, int port, uint32_t val)
{
	bzero(&ataio->cmd, sizeof(ataio->cmd));
	ataio->cmd.flags = 0;
	ataio->cmd.command = ATA_WRITE_PM;
	ataio->cmd.features = reg;
	ataio->cmd.sector_count = val;
	ataio->cmd.lba_low = val >> 8;
	ataio->cmd.lba_mid = val >> 16;
	ataio->cmd.lba_high = val >> 24;
	ataio->cmd.device = port & 0x0f;
}