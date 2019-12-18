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
typedef  int u_int8_t ;
struct TYPE_3__ {int feature; int count; int lba; int command; } ;
struct TYPE_4__ {TYPE_1__ ata; } ;
struct ata_request {int flags; TYPE_2__ u; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int ATA_A_4BIT ; 
 int ATA_COMMAND ; 
 int ATA_COUNT ; 
 int ATA_CYL_LSB ; 
 int ATA_CYL_MSB ; 
 int ATA_DEV (int /*<<< orphan*/ ) ; 
 int ATA_DRIVE ; 
 int ATA_D_IBM ; 
 int ATA_D_LBA ; 
 int ATA_FEATURE ; 
 int ATA_PDC_1B ; 
 int ATA_PDC_2B ; 
 int ATA_PDC_WAIT_NBUSY ; 
 int ATA_PDC_WRITE_CTL ; 
 int ATA_PDC_WRITE_END ; 
 int ATA_PDC_WRITE_REG ; 
 int ATA_R_48BIT ; 
 int ATA_SECTOR ; 

__attribute__((used)) static int
ata_promise_apkt(u_int8_t *bytep, struct ata_request *request)
{ 
    int i = 12;

    bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_PDC_WAIT_NBUSY|ATA_DRIVE;
    bytep[i++] = ATA_D_IBM | ATA_D_LBA | ATA_DEV(request->unit);
    bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_CTL;
    bytep[i++] = ATA_A_4BIT;

    if (request->flags & ATA_R_48BIT) {
	bytep[i++] = ATA_PDC_2B | ATA_PDC_WRITE_REG | ATA_FEATURE;
	bytep[i++] = request->u.ata.feature >> 8;
	bytep[i++] = request->u.ata.feature;
	bytep[i++] = ATA_PDC_2B | ATA_PDC_WRITE_REG | ATA_COUNT;
	bytep[i++] = request->u.ata.count >> 8;
	bytep[i++] = request->u.ata.count;
	bytep[i++] = ATA_PDC_2B | ATA_PDC_WRITE_REG | ATA_SECTOR;
	bytep[i++] = request->u.ata.lba >> 24;
	bytep[i++] = request->u.ata.lba;
	bytep[i++] = ATA_PDC_2B | ATA_PDC_WRITE_REG | ATA_CYL_LSB;
	bytep[i++] = request->u.ata.lba >> 32;
	bytep[i++] = request->u.ata.lba >> 8;
	bytep[i++] = ATA_PDC_2B | ATA_PDC_WRITE_REG | ATA_CYL_MSB;
	bytep[i++] = request->u.ata.lba >> 40;
	bytep[i++] = request->u.ata.lba >> 16;
	bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_DRIVE;
	bytep[i++] = ATA_D_LBA | ATA_DEV(request->unit);
    }
    else {
	bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_FEATURE;
	bytep[i++] = request->u.ata.feature;
	bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_COUNT;
	bytep[i++] = request->u.ata.count;
	bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_SECTOR;
	bytep[i++] = request->u.ata.lba;
	bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_CYL_LSB;
	bytep[i++] = request->u.ata.lba >> 8;
	bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_CYL_MSB;
	bytep[i++] = request->u.ata.lba >> 16;
	bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_REG | ATA_DRIVE;
	bytep[i++] = ATA_D_LBA | ATA_D_IBM | ATA_DEV(request->unit) |
		     ((request->u.ata.lba >> 24)&0xf);
    }
    bytep[i++] = ATA_PDC_1B | ATA_PDC_WRITE_END | ATA_COMMAND;
    bytep[i++] = request->u.ata.command;
    return i;
}