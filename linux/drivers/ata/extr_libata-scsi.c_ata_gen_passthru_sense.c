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
typedef  int u8 ;
struct scsi_cmnd {unsigned char* sense_buffer; int result; } ;
struct ata_taskfile {int command; unsigned char feature; unsigned char nsect; unsigned char lbal; unsigned char lbam; unsigned char lbah; unsigned char device; int flags; unsigned char hob_nsect; unsigned char hob_lbal; unsigned char hob_lbam; unsigned char hob_lbah; } ;
struct ata_queued_cmd {int /*<<< orphan*/  dev; TYPE_2__* ap; scalar_t__ err_mask; struct ata_taskfile result_tf; struct scsi_cmnd* scsicmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  print_id; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/ * error_handler; } ;

/* Variables and functions */
 int ATA_BUSY ; 
 int ATA_DF ; 
 int ATA_DRQ ; 
 int ATA_ERR ; 
 int ATA_TFLAG_LBA48 ; 
 int DRIVER_SENSE ; 
 int /*<<< orphan*/  RECOVERED_ERROR ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  ata_scsi_set_sense (int /*<<< orphan*/ ,struct scsi_cmnd*,int,int,int) ; 
 int /*<<< orphan*/  ata_to_sense_error (int /*<<< orphan*/ ,int,unsigned char,int*,int*,int*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_sense_desc_find (unsigned char*,int,int) ; 

__attribute__((used)) static void ata_gen_passthru_sense(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *cmd = qc->scsicmd;
	struct ata_taskfile *tf = &qc->result_tf;
	unsigned char *sb = cmd->sense_buffer;
	unsigned char *desc = sb + 8;
	int verbose = qc->ap->ops->error_handler == NULL;
	u8 sense_key, asc, ascq;

	memset(sb, 0, SCSI_SENSE_BUFFERSIZE);

	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	/*
	 * Use ata_to_sense_error() to map status register bits
	 * onto sense key, asc & ascq.
	 */
	if (qc->err_mask ||
	    tf->command & (ATA_BUSY | ATA_DF | ATA_ERR | ATA_DRQ)) {
		ata_to_sense_error(qc->ap->print_id, tf->command, tf->feature,
				   &sense_key, &asc, &ascq, verbose);
		ata_scsi_set_sense(qc->dev, cmd, sense_key, asc, ascq);
	} else {
		/*
		 * ATA PASS-THROUGH INFORMATION AVAILABLE
		 * Always in descriptor format sense.
		 */
		scsi_build_sense_buffer(1, cmd->sense_buffer,
					RECOVERED_ERROR, 0, 0x1D);
	}

	if ((cmd->sense_buffer[0] & 0x7f) >= 0x72) {
		u8 len;

		/* descriptor format */
		len = sb[7];
		desc = (char *)scsi_sense_desc_find(sb, len + 8, 9);
		if (!desc) {
			if (SCSI_SENSE_BUFFERSIZE < len + 14)
				return;
			sb[7] = len + 14;
			desc = sb + 8 + len;
		}
		desc[0] = 9;
		desc[1] = 12;
		/*
		 * Copy registers into sense buffer.
		 */
		desc[2] = 0x00;
		desc[3] = tf->feature;	/* == error reg */
		desc[5] = tf->nsect;
		desc[7] = tf->lbal;
		desc[9] = tf->lbam;
		desc[11] = tf->lbah;
		desc[12] = tf->device;
		desc[13] = tf->command; /* == status reg */

		/*
		 * Fill in Extend bit, and the high order bytes
		 * if applicable.
		 */
		if (tf->flags & ATA_TFLAG_LBA48) {
			desc[2] |= 0x01;
			desc[4] = tf->hob_nsect;
			desc[6] = tf->hob_lbal;
			desc[8] = tf->hob_lbam;
			desc[10] = tf->hob_lbah;
		}
	} else {
		/* Fixed sense format */
		desc[0] = tf->feature;
		desc[1] = tf->command; /* status */
		desc[2] = tf->device;
		desc[3] = tf->nsect;
		desc[7] = 0;
		if (tf->flags & ATA_TFLAG_LBA48)  {
			desc[8] |= 0x80;
			if (tf->hob_nsect)
				desc[8] |= 0x40;
			if (tf->hob_lbal || tf->hob_lbam || tf->hob_lbah)
				desc[8] |= 0x20;
		}
		desc[9] = tf->lbal;
		desc[10] = tf->lbam;
		desc[11] = tf->lbah;
	}
}