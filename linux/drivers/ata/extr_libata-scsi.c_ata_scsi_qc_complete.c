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
struct scsi_cmnd {int* cmnd; int /*<<< orphan*/  result; } ;
struct ata_queued_cmd {scalar_t__ err_mask; int flags; int /*<<< orphan*/  result_tf; struct scsi_cmnd* scsicmd; struct ata_port* ap; } ;
struct ata_port {int /*<<< orphan*/  print_id; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int ATA_12 ; 
 int ATA_16 ; 
 int ATA_QCFLAG_SENSE_VALID ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  ata_dump_status (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_gen_ata_sense (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_gen_passthru_sense (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_qc_done (struct ata_queued_cmd*) ; 

__attribute__((used)) static void ata_scsi_qc_complete(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct scsi_cmnd *cmd = qc->scsicmd;
	u8 *cdb = cmd->cmnd;
	int need_sense = (qc->err_mask != 0);

	/* For ATA pass thru (SAT) commands, generate a sense block if
	 * user mandated it or if there's an error.  Note that if we
	 * generate because the user forced us to [CK_COND =1], a check
	 * condition is generated and the ATA register values are returned
	 * whether the command completed successfully or not. If there
	 * was no error, we use the following sense data:
	 * sk = RECOVERED ERROR
	 * asc,ascq = ATA PASS-THROUGH INFORMATION AVAILABLE
	 */
	if (((cdb[0] == ATA_16) || (cdb[0] == ATA_12)) &&
	    ((cdb[2] & 0x20) || need_sense))
		ata_gen_passthru_sense(qc);
	else if (qc->flags & ATA_QCFLAG_SENSE_VALID)
		cmd->result = SAM_STAT_CHECK_CONDITION;
	else if (need_sense)
		ata_gen_ata_sense(qc);
	else
		cmd->result = SAM_STAT_GOOD;

	if (need_sense && !ap->ops->error_handler)
		ata_dump_status(ap->print_id, &qc->result_tf);

	ata_qc_done(qc);
}