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
struct ata_taskfile {int /*<<< orphan*/  command; int /*<<< orphan*/  protocol; int /*<<< orphan*/  flags; } ;
struct ata_queued_cmd {int /*<<< orphan*/  flags; TYPE_1__* dev; struct ata_taskfile tf; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_FLUSH ; 
 int /*<<< orphan*/  ATA_CMD_FLUSH_EXT ; 
 int ATA_DFLAG_FLUSH_EXT ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int /*<<< orphan*/  ATA_QCFLAG_IO ; 
 int /*<<< orphan*/  ATA_TFLAG_DEVICE ; 

__attribute__((used)) static unsigned int ata_scsi_flush_xlat(struct ata_queued_cmd *qc)
{
	struct ata_taskfile *tf = &qc->tf;

	tf->flags |= ATA_TFLAG_DEVICE;
	tf->protocol = ATA_PROT_NODATA;

	if (qc->dev->flags & ATA_DFLAG_FLUSH_EXT)
		tf->command = ATA_CMD_FLUSH_EXT;
	else
		tf->command = ATA_CMD_FLUSH;

	/* flush is critical for IO integrity, consider it an IO command */
	qc->flags |= ATA_QCFLAG_IO;

	return 0;
}