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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct ata_port {int /*<<< orphan*/  lock; } ;
struct ata_device {scalar_t__ n_sectors; scalar_t__ n_native_sectors; TYPE_2__* link; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  action; } ;
struct TYPE_4__ {TYPE_1__ eh_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DFLAG_UNLOCK_HPA ; 
 int /*<<< orphan*/  ATA_EH_RESET ; 
 int /*<<< orphan*/  ata_port_schedule_eh (struct ata_port*) ; 
 int /*<<< orphan*/  ata_port_wait_eh (struct ata_port*) ; 
 struct ata_device* ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_scsi_unlock_native_capacity(struct scsi_device *sdev)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);
	struct ata_device *dev;
	unsigned long flags;

	spin_lock_irqsave(ap->lock, flags);

	dev = ata_scsi_find_dev(ap, sdev);
	if (dev && dev->n_sectors < dev->n_native_sectors) {
		dev->flags |= ATA_DFLAG_UNLOCK_HPA;
		dev->link->eh_info.action |= ATA_EH_RESET;
		ata_port_schedule_eh(ap);
	}

	spin_unlock_irqrestore(ap->lock, flags);
	ata_port_wait_eh(ap);
}