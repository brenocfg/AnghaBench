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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct scsi_cmnd {int* cmnd; } ;
struct ata_taskfile {int flags; int feature; int lbam; int lbah; int nsect; int lbal; int /*<<< orphan*/  command; int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {TYPE_1__* dev; struct ata_taskfile tf; struct scsi_cmnd* scsicmd; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ATA_DFLAG_PIO ; 
 int /*<<< orphan*/  ATA_PROT_DMA ; 
 int /*<<< orphan*/  ATA_PROT_PIO ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA ; 
 int ATA_TFLAG_WRITE ; 
 int const SECURITY_PROTOCOL_OUT ; 
 int /*<<< orphan*/  ata_qc_set_pc_nbytes (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_scsi_set_invalid_field (TYPE_1__*,struct scsi_cmnd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_scsi_trusted_op (int,int,int) ; 
 int get_unaligned_be16 (int const*) ; 
 int get_unaligned_be32 (int const*) ; 

__attribute__((used)) static unsigned int ata_scsi_security_inout_xlat(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;
	const u8 *cdb = scmd->cmnd;
	struct ata_taskfile *tf = &qc->tf;
	u8 secp = cdb[1];
	bool send = (cdb[0] == SECURITY_PROTOCOL_OUT);
	u16 spsp = get_unaligned_be16(&cdb[2]);
	u32 len = get_unaligned_be32(&cdb[6]);
	bool dma = !(qc->dev->flags & ATA_DFLAG_PIO);

	/*
	 * We don't support the ATA "security" protocol.
	 */
	if (secp == 0xef) {
		ata_scsi_set_invalid_field(qc->dev, scmd, 1, 0);
		return 1;
	}

	if (cdb[4] & 7) { /* INC_512 */
		if (len > 0xffff) {
			ata_scsi_set_invalid_field(qc->dev, scmd, 6, 0);
			return 1;
		}
	} else {
		if (len > 0x01fffe00) {
			ata_scsi_set_invalid_field(qc->dev, scmd, 6, 0);
			return 1;
		}

		/* convert to the sector-based ATA addressing */
		len = (len + 511) / 512;
	}

	tf->protocol = dma ? ATA_PROT_DMA : ATA_PROT_PIO;
	tf->flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR | ATA_TFLAG_LBA;
	if (send)
		tf->flags |= ATA_TFLAG_WRITE;
	tf->command = ata_scsi_trusted_op(len, send, dma);
	tf->feature = secp;
	tf->lbam = spsp & 0xff;
	tf->lbah = spsp >> 8;

	if (len) {
		tf->nsect = len & 0xff;
		tf->lbal = len >> 8;
	} else {
		if (!send)
			tf->lbah = (1 << 7);
	}

	ata_qc_set_pc_nbytes(qc);
	return 0;
}