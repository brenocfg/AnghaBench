#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct scsi_cmnd {scalar_t__* cmnd; int cmd_len; int /*<<< orphan*/  result; } ;
struct ata_taskfile {int flags; scalar_t__ device; scalar_t__ lbah; scalar_t__ lbam; scalar_t__ lbal; scalar_t__ nsect; void* command; scalar_t__ hob_lbal; scalar_t__ hob_lbam; scalar_t__ hob_lbah; scalar_t__ hob_nsect; int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {struct ata_device* dev; struct ata_taskfile tf; struct scsi_cmnd* scsicmd; } ;
struct ata_device {scalar_t__ n_sectors; int flags; scalar_t__ sectors; scalar_t__ heads; } ;

/* Variables and functions */
 void* ATA_CMD_VERIFY ; 
 void* ATA_CMD_VERIFY_EXT ; 
 int ATA_DFLAG_LBA ; 
 int ATA_DFLAG_LBA48 ; 
 scalar_t__ ATA_LBA ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  DPRINTK (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 scalar_t__ const VERIFY ; 
 scalar_t__ const VERIFY_16 ; 
 int /*<<< orphan*/  ata_scsi_set_invalid_field (struct ata_device*,struct scsi_cmnd*,int,int) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (struct ata_device*,struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ lba_28_ok (scalar_t__,scalar_t__) ; 
 scalar_t__ lba_48_ok (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scsi_10_lba_len (scalar_t__ const*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  scsi_16_lba_len (scalar_t__ const*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static unsigned int ata_scsi_verify_xlat(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;
	struct ata_taskfile *tf = &qc->tf;
	struct ata_device *dev = qc->dev;
	u64 dev_sectors = qc->dev->n_sectors;
	const u8 *cdb = scmd->cmnd;
	u64 block;
	u32 n_block;
	u16 fp;

	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf->protocol = ATA_PROT_NODATA;

	if (cdb[0] == VERIFY) {
		if (scmd->cmd_len < 10) {
			fp = 9;
			goto invalid_fld;
		}
		scsi_10_lba_len(cdb, &block, &n_block);
	} else if (cdb[0] == VERIFY_16) {
		if (scmd->cmd_len < 16) {
			fp = 15;
			goto invalid_fld;
		}
		scsi_16_lba_len(cdb, &block, &n_block);
	} else {
		fp = 0;
		goto invalid_fld;
	}

	if (!n_block)
		goto nothing_to_do;
	if (block >= dev_sectors)
		goto out_of_range;
	if ((block + n_block) > dev_sectors)
		goto out_of_range;

	if (dev->flags & ATA_DFLAG_LBA) {
		tf->flags |= ATA_TFLAG_LBA;

		if (lba_28_ok(block, n_block)) {
			/* use LBA28 */
			tf->command = ATA_CMD_VERIFY;
			tf->device |= (block >> 24) & 0xf;
		} else if (lba_48_ok(block, n_block)) {
			if (!(dev->flags & ATA_DFLAG_LBA48))
				goto out_of_range;

			/* use LBA48 */
			tf->flags |= ATA_TFLAG_LBA48;
			tf->command = ATA_CMD_VERIFY_EXT;

			tf->hob_nsect = (n_block >> 8) & 0xff;

			tf->hob_lbah = (block >> 40) & 0xff;
			tf->hob_lbam = (block >> 32) & 0xff;
			tf->hob_lbal = (block >> 24) & 0xff;
		} else
			/* request too large even for LBA48 */
			goto out_of_range;

		tf->nsect = n_block & 0xff;

		tf->lbah = (block >> 16) & 0xff;
		tf->lbam = (block >> 8) & 0xff;
		tf->lbal = block & 0xff;

		tf->device |= ATA_LBA;
	} else {
		/* CHS */
		u32 sect, head, cyl, track;

		if (!lba_28_ok(block, n_block))
			goto out_of_range;

		/* Convert LBA to CHS */
		track = (u32)block / dev->sectors;
		cyl   = track / dev->heads;
		head  = track % dev->heads;
		sect  = (u32)block % dev->sectors + 1;

		DPRINTK("block %u track %u cyl %u head %u sect %u\n",
			(u32)block, track, cyl, head, sect);

		/* Check whether the converted CHS can fit.
		   Cylinder: 0-65535
		   Head: 0-15
		   Sector: 1-255*/
		if ((cyl >> 16) || (head >> 4) || (sect >> 8) || (!sect))
			goto out_of_range;

		tf->command = ATA_CMD_VERIFY;
		tf->nsect = n_block & 0xff; /* Sector count 0 means 256 sectors */
		tf->lbal = sect;
		tf->lbam = cyl;
		tf->lbah = cyl >> 8;
		tf->device |= head;
	}

	return 0;

invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, 0xff);
	return 1;

out_of_range:
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x21, 0x0);
	/* "Logical Block Address out of range" */
	return 1;

nothing_to_do:
	scmd->result = SAM_STAT_GOOD;
	return 1;
}