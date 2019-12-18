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
struct ata_queued_cmd {TYPE_2__* scsicmd; int /*<<< orphan*/  flags; struct ata_port* ap; } ;
struct ata_port {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  request; } ;
struct TYPE_3__ {int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_QCFLAG_FAILED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_eh_set_pending (struct ata_port*,int) ; 
 int /*<<< orphan*/  blk_abort_request (int /*<<< orphan*/ ) ; 

void ata_qc_schedule_eh(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	WARN_ON(!ap->ops->error_handler);

	qc->flags |= ATA_QCFLAG_FAILED;
	ata_eh_set_pending(ap, 1);

	/* The following will fail if timeout has already expired.
	 * ata_scsi_error() takes care of such scmds on EH entry.
	 * Note that ATA_QCFLAG_FAILED is unconditionally set after
	 * this function completes.
	 */
	blk_abort_request(qc->scsicmd->request);
}