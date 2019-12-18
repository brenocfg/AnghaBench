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
struct ata_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  pflags; } ;
struct ata_eh_context {int saved_ncq_enabled; scalar_t__* saved_xfer_mode; int /*<<< orphan*/  i; } ;
struct ata_link {struct ata_eh_context eh_context; int /*<<< orphan*/  eh_info; struct ata_port* ap; } ;
struct ata_device {size_t devno; int /*<<< orphan*/  flags; struct ata_link* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DFLAG_DETACH ; 
 int /*<<< orphan*/  ATA_DFLAG_DETACHED ; 
 int /*<<< orphan*/  ATA_EH_PERDEV_MASK ; 
 int /*<<< orphan*/  ATA_PFLAG_SCSI_HOTPLUG ; 
 int /*<<< orphan*/  ata_dev_disable (struct ata_device*) ; 
 int /*<<< orphan*/  ata_eh_clear_action (struct ata_link*,struct ata_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ata_scsi_offline_dev (struct ata_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_eh_detach_dev(struct ata_device *dev)
{
	struct ata_link *link = dev->link;
	struct ata_port *ap = link->ap;
	struct ata_eh_context *ehc = &link->eh_context;
	unsigned long flags;

	ata_dev_disable(dev);

	spin_lock_irqsave(ap->lock, flags);

	dev->flags &= ~ATA_DFLAG_DETACH;

	if (ata_scsi_offline_dev(dev)) {
		dev->flags |= ATA_DFLAG_DETACHED;
		ap->pflags |= ATA_PFLAG_SCSI_HOTPLUG;
	}

	/* clear per-dev EH info */
	ata_eh_clear_action(link, dev, &link->eh_info, ATA_EH_PERDEV_MASK);
	ata_eh_clear_action(link, dev, &link->eh_context.i, ATA_EH_PERDEV_MASK);
	ehc->saved_xfer_mode[dev->devno] = 0;
	ehc->saved_ncq_enabled &= ~(1 << dev->devno);

	spin_unlock_irqrestore(ap->lock, flags);
}