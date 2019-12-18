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
struct ata_res {void* lba_high; void* lba_mid; void* lba_low; void* sector_count; void* lba_high_exp; void* lba_mid_exp; void* lba_low_exp; void* sector_count_exp; void* device; void* error; void* status; } ;
struct TYPE_2__ {struct ata_res res; } ;
union ccb {TYPE_1__ ataio; } ;
struct mvs_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ALTSTAT ; 
 int /*<<< orphan*/  ATA_A_HOB ; 
 int /*<<< orphan*/  ATA_CONTROL ; 
 int /*<<< orphan*/  ATA_COUNT ; 
 int /*<<< orphan*/  ATA_CYL_LSB ; 
 int /*<<< orphan*/  ATA_CYL_MSB ; 
 int /*<<< orphan*/  ATA_DRIVE ; 
 int /*<<< orphan*/  ATA_ERROR ; 
 void* ATA_INB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_SECTOR ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_tfd_read(device_t dev, union ccb *ccb)
{
	struct mvs_channel *ch = device_get_softc(dev);
	struct ata_res *res = &ccb->ataio.res;

	res->status = ATA_INB(ch->r_mem, ATA_ALTSTAT);
	res->error =  ATA_INB(ch->r_mem, ATA_ERROR);
	res->device = ATA_INB(ch->r_mem, ATA_DRIVE);
	ATA_OUTB(ch->r_mem, ATA_CONTROL, ATA_A_HOB);
	res->sector_count_exp = ATA_INB(ch->r_mem, ATA_COUNT);
	res->lba_low_exp = ATA_INB(ch->r_mem, ATA_SECTOR);
	res->lba_mid_exp = ATA_INB(ch->r_mem, ATA_CYL_LSB);
	res->lba_high_exp = ATA_INB(ch->r_mem, ATA_CYL_MSB);
	ATA_OUTB(ch->r_mem, ATA_CONTROL, 0);
	res->sector_count = ATA_INB(ch->r_mem, ATA_COUNT);
	res->lba_low = ATA_INB(ch->r_mem, ATA_SECTOR);
	res->lba_mid = ATA_INB(ch->r_mem, ATA_CYL_LSB);
	res->lba_high = ATA_INB(ch->r_mem, ATA_CYL_MSB);
}