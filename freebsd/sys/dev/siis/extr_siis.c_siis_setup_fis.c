#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int flags; int command; int features; int lba_low; int lba_mid; int lba_high; int device; int lba_low_exp; int lba_mid_exp; int lba_high_exp; int features_exp; int sector_count; int sector_count_exp; } ;
struct TYPE_16__ {int ata_flags; int aux; TYPE_7__ cmd; } ;
struct TYPE_11__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct TYPE_14__ {int dxfer_len; int /*<<< orphan*/  cdb_len; TYPE_3__ cdb_io; } ;
struct TYPE_10__ {int target_id; scalar_t__ func_code; int flags; } ;
union ccb {TYPE_8__ ataio; TYPE_6__ csio; TYPE_2__ ccb_h; } ;
typedef  int u_int8_t ;
struct TYPE_12__ {int* ccb; } ;
struct TYPE_13__ {TYPE_4__ atapi; } ;
struct siis_cmd {int* fis; TYPE_5__ u; } ;
struct siis_channel {TYPE_1__* curr; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_9__ {scalar_t__ mode; } ;

/* Variables and functions */
 int ATA_A_4BIT ; 
 scalar_t__ ATA_DMA ; 
 int ATA_D_LBA ; 
 int ATA_FLAG_AUX ; 
 int ATA_F_DMA ; 
 int ATA_PACKET_CMD ; 
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siis_setup_fis(device_t dev, struct siis_cmd *ctp, union ccb *ccb, int tag)
{
	struct siis_channel *ch = device_get_softc(dev);
	u_int8_t *fis = &ctp->fis[0];

	bzero(fis, 24);
	fis[0] = 0x27;  		/* host to device */
	fis[1] = (ccb->ccb_h.target_id & 0x0f);
	if (ccb->ccb_h.func_code == XPT_SCSI_IO) {
		fis[1] |= 0x80;
		fis[2] = ATA_PACKET_CMD;
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE &&
		    ch->curr[ccb->ccb_h.target_id].mode >= ATA_DMA)
			fis[3] = ATA_F_DMA;
		else {
			fis[5] = ccb->csio.dxfer_len;
		        fis[6] = ccb->csio.dxfer_len >> 8;
		}
		fis[7] = ATA_D_LBA;
		fis[15] = ATA_A_4BIT;
		bzero(ctp->u.atapi.ccb, 16);
		bcopy((ccb->ccb_h.flags & CAM_CDB_POINTER) ?
		    ccb->csio.cdb_io.cdb_ptr : ccb->csio.cdb_io.cdb_bytes,
		    ctp->u.atapi.ccb, ccb->csio.cdb_len);
	} else if ((ccb->ataio.cmd.flags & CAM_ATAIO_CONTROL) == 0) {
		fis[1] |= 0x80;
		fis[2] = ccb->ataio.cmd.command;
		fis[3] = ccb->ataio.cmd.features;
		fis[4] = ccb->ataio.cmd.lba_low;
		fis[5] = ccb->ataio.cmd.lba_mid;
		fis[6] = ccb->ataio.cmd.lba_high;
		fis[7] = ccb->ataio.cmd.device;
		fis[8] = ccb->ataio.cmd.lba_low_exp;
		fis[9] = ccb->ataio.cmd.lba_mid_exp;
		fis[10] = ccb->ataio.cmd.lba_high_exp;
		fis[11] = ccb->ataio.cmd.features_exp;
		if (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA) {
			fis[12] = tag << 3;
			fis[13] = 0;
		} else {
			fis[12] = ccb->ataio.cmd.sector_count;
			fis[13] = ccb->ataio.cmd.sector_count_exp;
		}
		fis[15] = ATA_A_4BIT;
		if (ccb->ataio.ata_flags & ATA_FLAG_AUX) {
			fis[16] =  ccb->ataio.aux        & 0xff;
			fis[17] = (ccb->ataio.aux >>  8) & 0xff;
			fis[18] = (ccb->ataio.aux >> 16) & 0xff;
			fis[19] = (ccb->ataio.aux >> 24) & 0xff;
		}
	} else {
		/* Soft reset. */
	}
	return (20);
}