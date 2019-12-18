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
struct scsi_device {struct request_queue* request_queue; int /*<<< orphan*/  host; } ;
struct request_queue {scalar_t__ dma_drain_size; int /*<<< orphan*/ * dma_drain_buffer; } ;
struct ata_port {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct ata_device {int /*<<< orphan*/  flags; int /*<<< orphan*/ * sdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DFLAG_DETACH ; 
 struct ata_device* __ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 int /*<<< orphan*/  ata_port_schedule_eh (struct ata_port*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_scsi_slave_destroy(struct scsi_device *sdev)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);
	struct request_queue *q = sdev->request_queue;
	unsigned long flags;
	struct ata_device *dev;

	if (!ap->ops->error_handler)
		return;

	spin_lock_irqsave(ap->lock, flags);
	dev = __ata_scsi_find_dev(ap, sdev);
	if (dev && dev->sdev) {
		/* SCSI device already in CANCEL state, no need to offline it */
		dev->sdev = NULL;
		dev->flags |= ATA_DFLAG_DETACH;
		ata_port_schedule_eh(ap);
	}
	spin_unlock_irqrestore(ap->lock, flags);

	kfree(q->dma_drain_buffer);
	q->dma_drain_buffer = NULL;
	q->dma_drain_size = 0;
}