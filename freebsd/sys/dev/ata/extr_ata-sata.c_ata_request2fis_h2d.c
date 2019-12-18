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
struct TYPE_3__ {int command; int feature; int lba; int count; } ;
struct TYPE_4__ {TYPE_1__ ata; } ;
struct ata_request {int flags; int unit; int transfersize; TYPE_2__ u; } ;

/* Variables and functions */
 int ATA_A_4BIT ; 
 int ATA_D_IBM ; 
 int ATA_D_LBA ; 
 int ATA_F_DMA ; 
 int ATA_PACKET_CMD ; 
 int ATA_R_48BIT ; 
 int ATA_R_ATAPI ; 
 int ATA_R_READ ; 
 int ATA_R_WRITE ; 

int
ata_request2fis_h2d(struct ata_request *request, u_int8_t *fis)
{

    if (request->flags & ATA_R_ATAPI) {
	fis[0] = 0x27;  		/* host to device */
	fis[1] = 0x80 | (request->unit & 0x0f);
	fis[2] = ATA_PACKET_CMD;
	if (request->flags & (ATA_R_READ | ATA_R_WRITE))
	    fis[3] = ATA_F_DMA;
	else {
	    fis[5] = request->transfersize;
	    fis[6] = request->transfersize >> 8;
	}
	fis[7] = ATA_D_LBA;
	fis[15] = ATA_A_4BIT;
	return 20;
    }
    else {
	fis[0] = 0x27;			/* host to device */
	fis[1] = 0x80 | (request->unit & 0x0f);
	fis[2] = request->u.ata.command;
	fis[3] = request->u.ata.feature;
	fis[4] = request->u.ata.lba;
	fis[5] = request->u.ata.lba >> 8;
	fis[6] = request->u.ata.lba >> 16;
	fis[7] = ATA_D_LBA;
	if (!(request->flags & ATA_R_48BIT))
	    fis[7] |= (ATA_D_IBM | (request->u.ata.lba >> 24 & 0x0f));
	fis[8] = request->u.ata.lba >> 24;
	fis[9] = request->u.ata.lba >> 32; 
	fis[10] = request->u.ata.lba >> 40; 
	fis[11] = request->u.ata.feature >> 8;
	fis[12] = request->u.ata.count;
	fis[13] = request->u.ata.count >> 8;
	fis[15] = ATA_A_4BIT;
	return 20;
    }
    return 0;
}