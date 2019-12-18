#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int feature; int count; int lba; } ;
struct TYPE_4__ {TYPE_1__ ata; } ;
struct ata_request {int flags; TYPE_2__ u; int /*<<< orphan*/  unit; int /*<<< orphan*/  parent; } ;
struct ata_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_COUNT ; 
 int /*<<< orphan*/  ATA_CYL_LSB ; 
 int /*<<< orphan*/  ATA_CYL_MSB ; 
 int ATA_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_DRIVE ; 
 int ATA_D_IBM ; 
 int ATA_D_LBA ; 
 int /*<<< orphan*/  ATA_FEATURE ; 
 int /*<<< orphan*/  ATA_IDX_OUTW (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int ATA_R_48BIT ; 
 int /*<<< orphan*/  ATA_SECTOR ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_serverworks_tf_write(struct ata_request *request)
{
    struct ata_channel *ch = device_get_softc(request->parent);

    if (request->flags & ATA_R_48BIT) {
	ATA_IDX_OUTW(ch, ATA_FEATURE, request->u.ata.feature);
	ATA_IDX_OUTW(ch, ATA_COUNT, request->u.ata.count);
	ATA_IDX_OUTW(ch, ATA_SECTOR, ((request->u.ata.lba >> 16) & 0xff00) |
				      (request->u.ata.lba & 0x00ff));
	ATA_IDX_OUTW(ch, ATA_CYL_LSB, ((request->u.ata.lba >> 24) & 0xff00) |
				       ((request->u.ata.lba >> 8) & 0x00ff));
	ATA_IDX_OUTW(ch, ATA_CYL_MSB, ((request->u.ata.lba >> 32) & 0xff00) | 
				       ((request->u.ata.lba >> 16) & 0x00ff));
	ATA_IDX_OUTW(ch, ATA_DRIVE, ATA_D_LBA | ATA_DEV(request->unit));
    }
    else {
	ATA_IDX_OUTW(ch, ATA_FEATURE, request->u.ata.feature);
	ATA_IDX_OUTW(ch, ATA_COUNT, request->u.ata.count);
	    ATA_IDX_OUTW(ch, ATA_SECTOR, request->u.ata.lba);
	    ATA_IDX_OUTW(ch, ATA_CYL_LSB, request->u.ata.lba >> 8);
	    ATA_IDX_OUTW(ch, ATA_CYL_MSB, request->u.ata.lba >> 16);
	    ATA_IDX_OUTW(ch, ATA_DRIVE,
			 ATA_D_IBM | ATA_D_LBA | ATA_DEV(request->unit) |
			 ((request->u.ata.lba >> 24) & 0x0f));
    }
}