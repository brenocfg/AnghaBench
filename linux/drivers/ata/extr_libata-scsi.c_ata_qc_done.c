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
struct scsi_cmnd {int dummy; } ;
struct ata_queued_cmd {void (* scsidone ) (struct scsi_cmnd*) ;struct scsi_cmnd* scsicmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_qc_free (struct ata_queued_cmd*) ; 

__attribute__((used)) static void ata_qc_done(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *cmd = qc->scsicmd;
	void (*done)(struct scsi_cmnd *) = qc->scsidone;

	ata_qc_free(qc);
	done(cmd);
}