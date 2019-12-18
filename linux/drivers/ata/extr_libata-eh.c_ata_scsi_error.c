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
struct ata_port {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  eh_cmd_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_scsi_cmd_error_handler (struct Scsi_Host*,struct ata_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_scsi_port_error_handler (struct Scsi_Host*,struct ata_port*) ; 
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 int /*<<< orphan*/  eh_work_q ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_scsi_error(struct Scsi_Host *host)
{
	struct ata_port *ap = ata_shost_to_port(host);
	unsigned long flags;
	LIST_HEAD(eh_work_q);

	DPRINTK("ENTER\n");

	spin_lock_irqsave(host->host_lock, flags);
	list_splice_init(&host->eh_cmd_q, &eh_work_q);
	spin_unlock_irqrestore(host->host_lock, flags);

	ata_scsi_cmd_error_handler(host, ap, &eh_work_q);

	/* If we timed raced normal completion and there is nothing to
	   recover nr_timedout == 0 why exactly are we doing error recovery ? */
	ata_scsi_port_error_handler(host, ap);

	/* finish or retry handled scmd's and clean up */
	WARN_ON(!list_empty(&eh_work_q));

	DPRINTK("EXIT\n");
}