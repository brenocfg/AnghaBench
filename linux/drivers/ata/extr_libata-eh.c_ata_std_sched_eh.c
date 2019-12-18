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
struct ata_port {int pflags; int /*<<< orphan*/  scsi_host; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int ATA_PFLAG_INITIALIZING ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_eh_set_pending (struct ata_port*,int) ; 
 int /*<<< orphan*/  scsi_schedule_eh (int /*<<< orphan*/ ) ; 

void ata_std_sched_eh(struct ata_port *ap)
{
	WARN_ON(!ap->ops->error_handler);

	if (ap->pflags & ATA_PFLAG_INITIALIZING)
		return;

	ata_eh_set_pending(ap, 1);
	scsi_schedule_eh(ap->scsi_host);

	DPRINTK("port EH scheduled\n");
}