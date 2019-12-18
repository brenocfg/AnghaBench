#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; int command; int features; int lba_low; int lba_mid; int lba_high; int device; int lba_low_exp; int lba_mid_exp; int lba_high_exp; int features_exp; int sector_count; int sector_count_exp; int control; } ;
struct TYPE_12__ {TYPE_5__ cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct TYPE_10__ {int dxfer_len; int cdb_len; TYPE_3__ cdb_io; } ;
struct TYPE_8__ {int target_id; scalar_t__ func_code; int flags; } ;
union ccb {TYPE_6__ ataio; TYPE_4__ csio; TYPE_2__ ccb_h; } ;
typedef  int uint8_t ;
struct fsl_sata_cmd_tab {int* cfis; int* acmd; } ;
struct fsl_sata_channel {TYPE_1__* curr; } ;
struct TYPE_7__ {scalar_t__ mode; } ;

/* Variables and functions */
 int ATA_A_4BIT ; 
 scalar_t__ ATA_DMA ; 
 int ATA_D_LBA ; 
 int ATA_F_DMA ; 
 int ATA_PACKET_CMD ; 
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_CDB_POINTER ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 

__attribute__((used)) static int
fsl_sata_setup_fis(struct fsl_sata_channel *ch, struct fsl_sata_cmd_tab *ctp, union ccb *ccb, int tag)
{
	uint8_t *fis = &ctp->cfis[0];

	bzero(fis, 32);
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
		bcopy((ccb->ccb_h.flags & CAM_CDB_POINTER) ?
		    ccb->csio.cdb_io.cdb_ptr : ccb->csio.cdb_io.cdb_bytes,
		    ctp->acmd, ccb->csio.cdb_len);
		bzero(ctp->acmd + ccb->csio.cdb_len, 32 - ccb->csio.cdb_len);
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
	} else {
		fis[15] = ccb->ataio.cmd.control;
	}
	return (20);
}